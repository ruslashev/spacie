#ifndef PAINTER_HPP
#define PAINTER_HPP

#include <SDL2/SDL.h>

class Painter
{
	SDL_Window *_window;
	SDL_GLContext _gl_context;
	SDL_Event _event;

	const unsigned int WindowWidth;
	const unsigned int WindowHeight;

	void init_SDL_calls();

public:
	bool Quit;

	Painter();
	~Painter();

	void HandleInput();
	void Draw();
};

#endif

