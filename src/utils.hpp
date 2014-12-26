#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdarg>
#include <fstream>
#include <stdexcept>
#include <string>

void assertf(bool condition, const char *format, ...);

void errorf(const char *format, ...);

struct File {
	size_t size;
	std::string contents;
};
File readFile(std::string path);

#endif

