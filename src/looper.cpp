#include "looper.hpp"

void Looper::MainLoop()
{
	Painter painter;
	_painter_ptr = &painter;
	_quit = false;

	_old_time = 0;

	while (!_quit) {
		handleInput();

		_new_time = SDL_GetTicks();
		unsigned int time_difference = _new_time - _old_time;

		painter.Update(time_difference, _new_time);

		painter.Draw();
	}
}

void Looper::handleInput()
{
	if (SDL_PollEvent(&_event)) {
		if (_event.type == SDL_QUIT)
			_quit = true;
		if (_event.type == SDL_KEYUP &&
				_event.key.keysym.sym == SDLK_ESCAPE)
			_quit = true;
		if (_event.type == SDL_WINDOWEVENT_RESIZED)
			_painter_ptr->opengl.Resize(
					_event.window.data1,
					_event.window.data2);
	}
}

