#ifndef LOG_H
#define LOG_H
#include <stdio.h>
// #include <string>
// class Log
// {
// public:
// 	Log();
// 	~Log();
// 	static void D(std::string);

// };
#define TRACE(format, ...) printf(format, ##__VA_ARGS__);

#endif