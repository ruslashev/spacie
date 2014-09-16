#include <stdexcept>

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

