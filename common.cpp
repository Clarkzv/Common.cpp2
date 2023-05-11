#include <common.h>
#include <ctime>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

time_t Str2Timestamp(const std::string& timeStamp) {
    struct tm tm = {};
    sscanf(timeStamp.c_str(), "%d-%d-%dT%d:%d:%d",
           &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
           &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
    if (tm.tm_year < 1900 || tm.tm_mon < 1) {
        return 0;
    }
    tm.tm_year -= 1900;
    tm.tm_mon--;
    return mktime(&tm);
}

std::string Timestamp2Str(time_t t) {
    struct tm tm = {};
    gmtime(&t);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%dT%H:%M:%S", &tm);
    return std::string(buffer);
}

bool Str2Int64(const std::string& s, int64_t* v) {
    char* endPtr = NULL;
    auto vv = strtoll(s.c_str(), &endPtr, 10);
    if (endPtr == s.c_str()) {
        return false;
    }
    *v = vv;
    return true;
}

std::string Int64Str(int64_t v) {
    char buf[20] = { 0 };
    snprintf(buf, sizeof(buf), "%lld", v);
    return buf;
}

std::string FormatStr(const char* format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 255, format, args);
    va_end(args);
    return buffer;
}

bool ParseHost(const std::string& addr, std::string& host, int& port) {
    int portPos = (int)addr.find_last_of(":");
    if (portPos < 0) {
        return false;
    }
    int64_t port__ = 0;
    if (!Str2Int64(addr.substr(portPos + 1), &port__)) {
        return false;
    }
    host = addr.substr(0, portPos);
    port = int(port__);
    return true;
}
