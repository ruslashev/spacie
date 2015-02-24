#ifndef LOOPER_HPP
#define LOOPER_HPP

#include "painter.hpp"

#include <SDL2/SDL.h>

class Looper
{
	SDL_Event _event;
	Painter *_painter_ptr;
	bool _quit;
	unsigned int _old_time, _new_time;

	void handleInput();
public:
	void MainLoop();
};

#endif

