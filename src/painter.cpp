#include "painter.hpp"

Painter::Painter() : _window_width(800), _window_height(600)
{
	init_do_SDL_calls();

	glewExperimental = GL_TRUE;
	GLenum glewstatus = glewInit();
	assertf(glewstatus == GLEW_OK, "%s", glewGetErrorString(glewstatus));

	opengl.Construct(_window_width, _window_height);
}

void Painter::Update(unsigned int dt, unsigned int t)
{
	opengl.Update(dt, t);
}

void Painter::Draw()
{
	opengl.Draw();

	SDL_GL_SwapWindow(_window);
}

void Painter::init_do_SDL_calls()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	_window = SDL_CreateWindow("Spacie",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			_window_width, _window_height,
			SDL_WINDOW_OPENGL);

	_gl_context = SDL_GL_CreateContext(_window);
}

Painter::~Painter()
{
	SDL_GL_DeleteContext(_gl_context);

	SDL_Quit();
}

