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
#define RED_ERROR "\x1b[31m" "ERROR" "\x1b[0m" " "
	try {
		startGame();
	} catch (std::bad_alloc &ba) {
		fprintf(stderr, RED_ERROR);
		fprintf(stderr, "Failed to allocate memory: %s\n", ba.what());
		return 1;
	} catch (std::exception &e) {
		fprintf(stderr, RED_ERROR);
		fprintf(stderr, "%s\n", e.what());
		return 1;
	}

	return 0;
}

