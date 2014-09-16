#include "painter.hpp"

Painter::Painter() : WindowWidth(800), WindowHeight(600)
{
	init_SDL_calls();

	_window = SDL_CreateWindow("Spacie",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WindowWidth, WindowHeight,
			SDL_WINDOW_OPENGL);

	_gl_context = SDL_GL_CreateContext(_window);

	Quit = false;
}

void Painter::init_SDL_calls()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
}

Painter::~Painter()
{
	SDL_GL_DeleteContext(_gl_context);

	SDL_Quit();
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

