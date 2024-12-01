#include "diag.hh"

void diagE(std::string code, int line, int col, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    ::std::cerr << code << ::std::endl;
    ::fprintf(stderr, "%*s^\n", col, "");
    ::vfprintf(stderr, fmt, ap);
    ::fprintf(stderr, "\n");
    va_end(ap);
    ::exit(0);
}