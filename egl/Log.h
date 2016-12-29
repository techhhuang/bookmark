#ifndef LOG_H
#define LOG_H
#include <stdio.h>

#define TAG "SMARTUI"
#define TRACE(fmt,...) printf("%s: %s %d: " fmt,TAG,__FILE__,__LINE__,##__VA_ARGS__);

#endif