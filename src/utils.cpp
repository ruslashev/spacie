#include "utils.hpp"

void assertf(bool condition, const char *format, ...)
{
#ifndef RELEASE
	if (!condition) {
		char output[512];
		va_list args;
		va_start(args, format);
		vsnprintf(output, 512, format, args);
		va_end(args);
		throw std::runtime_error(output);
	}
#endif
}

void errorf(const char *format, ...)
{
    char output[512];
    va_list args;
    va_start(args, format);
    vsnprintf(output, 512, format, args);
    va_end(args);
    throw std::runtime_error(output);
}

std::string readFile(std::string path)
{
	std::ifstream ifs(path.c_str(), std::ifstream::binary);
	assertf(ifs, "Failed to open file \"%s\" for reading.", path.c_str());

	ifs.seekg(0, ifs.end);
	const int filesize = ifs.tellg();
	ifs.seekg(0, ifs.beg);

	char *buffer = new char [filesize];

	ifs.read(buffer, filesize);

	int read = ifs.gcount();
	double percent = 100.*read/(double)filesize;
	assertf(ifs, "Only %d characters (%.2f%%) read from file \"%s\"",
			read, percent, path.c_str());

	ifs.close();

	std::string buf_str(buffer);

	delete[] buffer;

	return buf_str;
}

