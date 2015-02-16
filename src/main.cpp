#include <stdexcept>
#include "painter.hpp"

void startGame()
{
	Painter painter;

	while (!painter.Quit) {
		painter.HandleInput();
		painter.Draw();
	}
}

int main()
{
	const char *ansiRed = "\x1b[31m",
		  *ansiNormal = "\x1b[0m";

	try {
		startGame();
	} catch (std::bad_alloc &ba) {
		fprintf(stderr, ansiRed);
		fprintf(stderr, "Failed to allocate memory: %s", ba.what());
		fprintf(stderr, "%s\n", ansiNormal);
		return 1;
	} catch (std::exception &e) {
		fprintf(stderr, ansiRed);
		fprintf(stderr, "%s", e.what());
		fprintf(stderr, "%s\n", ansiNormal);
		return 1;
	}

	return 0;
}

