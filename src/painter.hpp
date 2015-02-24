#ifndef PAINTER_HPP
#define PAINTER_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "opengl/opengl.hpp"
#include "utils.hpp"

class Painter
{
	SDL_Window *_window;
	SDL_GLContext _gl_context;

	const unsigned int _window_width;
	const unsigned int _window_height;

	void init_do_SDL_calls();
public:
	OpenGL opengl;

	Painter();
	~Painter();

	void Update(unsigned int dt, unsigned int t);
	void Draw();
};

#endif

