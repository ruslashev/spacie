#include <stdexcept>
#include "looper.hpp"
#include "utils.hpp"

int main()
{
	try {
		Looper looper;
		looper.MainLoop();
	} catch (std::bad_alloc &ba) {
		fprintf(stderr, "%s", AnsiColors.Red);
		fprintf(stderr, "Failed to allocate memory: %s", ba.what());
		fprintf(stderr, "%s\n", AnsiColors.Normal);
		return 1;
	} catch (std::exception &e) {
		fprintf(stderr, "%s", AnsiColors.Red);
		fprintf(stderr, "ERROR: %s", e.what());
		fprintf(stderr, "%s\n", AnsiColors.Normal);
		return 1;
	}

	return 0;
}

