#include "application.h"
#include <cold/render/impl/gl.h>
#include <cold/platform/os.h>
#include <cold/input/mouse.h>
#include <cold/input/keyboard.h>
#include <ostream>
#include <sstream>
#include <SDL_syswm.h>

namespace cold {

namespace {
	void liberror(const char *lb, const char* title, const char* s, const char* err) {
		std::stringstream ss = std::stringstream(std::stringstream::in);
		ss << s << "\n[" << lb << "] " << err;
		os::message_box(title, ss.str().c_str(), os::MBOX_ERROR);
	}
}

struct Application::Impl {
	HWND hwnd;
};

Application::Application()
	: surface(NULL)
	, run(true)
	, last_tick(0)
	, impl(new Impl)
{
}
Application::~Application() {
	SDL_Quit();
	delete impl;
}

static void set_gl_settings() {
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
 
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,        32);
 
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
 
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  0);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  0);

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 0 );
}

static Uint32 make_flags(Application::WindowType type) {
	Uint32 winflag = SDL_OPENGL;
	switch (type) {
	case Application::FULLSCREEN:
		winflag |= SDL_FULLSCREEN;
		break;
	case Application::WINDOW_NO_BORDER:
		winflag |= SDL_NOFRAME;
		break;
	}
	return winflag;
}

bool Application::update_window() {
	SDL_SysWMinfo wmi;
	SDL_VERSION(&wmi.version);
	if (!SDL_GetWMInfo(&wmi)) {
		liberror("SDL", "Error", "Could not get window manager info", SDL_GetError());
		return false;
	}

	impl->hwnd = wmi.window;
	if (window_placement == TOP_LEFT)
		SetWindowPos(impl->hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE);

	Keyboard::initialize();
	Mouse::set_lock_position(width / 2, height / 2);
	return true;
}

bool Application::create_window(unsigned int w, unsigned int h, unsigned int ms, WindowType type, WindowPlacement place) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		liberror("SDL", "Error", "Unable to init SDL", SDL_GetError());
		return false;
	}
	set_gl_settings();
	if (ms > 0) {
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  ms);
	}
	width = w;
	height = h;
	window_type = type;
	window_placement = place;
	if((surface = SDL_SetVideoMode(w, h, 32, make_flags(type))) < 0) {
		liberror("SDL", "Error", "Unable to set video mode", SDL_GetError());
		return false;
	}

	GLenum err = glewInit();
	if(err != GLEW_OK) {
		liberror("GLEW", "Error", "Failed to initialize GLEW", (const char*)glewGetErrorString(err));
		return false;
	}

	if (ms > 0)
		glEnable(GL_MULTISAMPLE);

	SDL_EnableKeyRepeat(0, 0);

	update_window();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	return true;
}

void Application::poll_events() {
	SDL_Event ev;
	Keyboard::update();
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type) {
		case SDL_ACTIVEEVENT:
			Mouse::set_active(ev.active.gain != 0);
			break;
		case SDL_QUIT:
			run = false;
			break;
		case SDL_KEYDOWN:
			Keyboard::set_key(ev.key.keysym.sym, true);
			if (Keyboard::is_reading()) { 
				if (ev.key.keysym.sym == SDLK_RETURN)
					Keyboard::write('\n');
				else
					Keyboard::write(ev.key.keysym.unicode);
			}
			break;
		case SDL_KEYUP:
			Keyboard::set_key(ev.key.keysym.sym, false);
			break;
		}
	}
	Mouse::update();
}

void Application::set_title(const char* title) {
	SDL_WM_SetCaption(title, title);
}

float Application::update_elapsed() {
	unsigned int tick = SDL_GetTicks();
	float dt = (float)(tick - last_tick) * 0.001f;
	last_tick = tick;
	return dt;
}

}