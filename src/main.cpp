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
	try {
		startGame();
	} catch (std::exception &e) {
		fprintf(stderr, "\x1b[31m" "ERROR" "\x1b[0m" " %s\n", e.what());
	}
}

