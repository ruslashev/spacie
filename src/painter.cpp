#include "painter.hpp"

Painter::Painter() : _window_width(800), _window_height(600)
{
	init_do_SDL_calls();

	init_assign_vars();

	glewExperimental = GL_TRUE;
	GLenum glewstatus = glewInit();
	assertf(glewstatus == GLEW_OK, "%s", glewGetErrorString(glewstatus));
}

void Painter::HandleInput()
{
	if (SDL_PollEvent(&_event)) {
		if (_event.type == SDL_QUIT)
			Quit = true;
		if (_event.type == SDL_KEYUP &&
				_event.key.keysym.sym == SDLK_ESCAPE)
			Quit = true;
	}
}

void Painter::Draw()
{
	SDL_GL_SwapWindow(_window);
}

void Painter::init_do_SDL_calls()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
}

void Painter::init_assign_vars()
{
	_window = SDL_CreateWindow("Spacie",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			_window_width, _window_height,
			SDL_WINDOW_OPENGL);

	_gl_context = SDL_GL_CreateContext(_window);

	Quit = false;
}

Painter::~Painter()
{
	SDL_GL_DeleteContext(_gl_context);

	SDL_Quit();
}

