#ifndef PAINTER_HPP
#define PAINTER_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "utils.hpp"

class Painter
{
	SDL_Window *_window;
	SDL_GLContext _gl_context;
	SDL_Event _event;

	const unsigned int _window_width;
	const unsigned int _window_height;

	void init_do_SDL_calls();
	void init_assign_vars();

public:
	bool Quit;

	Painter();
	~Painter();

	void HandleInput();
	void Draw();
};

#endif

