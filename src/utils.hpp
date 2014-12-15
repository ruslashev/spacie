#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdexcept>
#include <cstdarg>

void assertf(bool condition, const char *format, ...);
void errorf(const char *format, ...);

#endif

