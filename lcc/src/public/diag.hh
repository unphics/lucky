#ifndef diag_h
#define diag_h

#include <string>
#include <stdarg.h>
#include <iostream>

void diagE(std::string code, int line, int col, const char* fmt, ...);

// class diag {
// public:
// };


#endif