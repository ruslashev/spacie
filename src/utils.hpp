#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdarg>
#include <fstream>
#include <stdexcept>
#include <string>

void assertf(bool condition, const char *format, ...);

void errorf(const char *format, ...);

std::string readFile(std::string path);

#endif

