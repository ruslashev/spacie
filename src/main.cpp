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
#define RED_ERROR "\x1b[31m" "ERROR" "\x1b[0m"
	try {
		startGame();
	} catch (const std::bad_alloc&) {
		fputs(RED_ERROR " Failed to allocate memory\n", stderr);
	} catch (std::exception &e) {
		fprintf(stderr, RED_ERROR " %s\n", e.what());
	}
}

