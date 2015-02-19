#include <stdexcept>
#include "painter.hpp"
#include "utils.hpp"

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
	} catch (std::bad_alloc &ba) {
		fprintf(stderr, "%s", AnsiColors.Red);
		fprintf(stderr, "Failed to allocate memory: %s", ba.what());
		fprintf(stderr, "%s\n", AnsiColors.Normal);
		return 1;
	} catch (std::exception &e) {
		fprintf(stderr, "%s", AnsiColors.Red);
		fprintf(stderr, "%s", e.what());
		fprintf(stderr, "%s\n", AnsiColors.Normal);
		return 1;
	}

	return 0;
}

