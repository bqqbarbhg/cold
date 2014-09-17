#ifndef _COLD_PLATFORM_APPLICATION_H
#define _COLD_PLATFORM_APPLICATION_H

struct SDL_Surface;
namespace cold {

// Windowed application that holds a graphics device
class Application {
public:
	// Type of a window
	enum WindowType {
		// Default window style
		WINDOW,
		// Borderless window, can be combined with `WindowPlacement::TOP_LEFT`
		// to create borderless full screen window
		WINDOW_NO_BORDER,
		// Full screen (use direct drivers)
		FULLSCREEN,
	};
	// Placement mode of a window
	enum WindowPlacement {
		// Default window placement
		DEFAULT,
		// Try to move the window to the top-left corner of the main monitor
		TOP_LEFT,
	};
	Application();
	~Application();

	// Creates a window for the application
	// Must be called before any graphical object is created
	// or modified (for example a Shader or a VertexBuffer)
	// width: Width of the window
	// height: Height of the window
	// multisample: Samples to use antialiasing, 0 to turn antialiasing off
	// type: WINDOW, WINDOW_NO_BORDER or FULLSCREEN
	// place: DEFAULT or TOP_LEFT
	bool create_window(unsigned int width, unsigned int height, unsigned int multisample, WindowType type, WindowPlacement place);

	// Sets an title for the window
	// title: The title to set for the window
	void set_title(const char* title);

	// Polls the events from OS
	// Should be called every frame
	// Updates `input/mouse` and `input/keyboard`
	void poll_events();

	// Quits the application
	// Not immediate, has to be checked with `is_running`
	void quit() { run = false; }

	// Returns whether the application is running
	// Should be used as the condition for the main loop
	bool is_running() { return run; }

	// Returns the duration from when `update_elapsed` was last called
	// Should be called every time after the program can stall so the
	// lag spikes won't affect the elapsed time of the simulation
	float update_elapsed();

	// Returns the width of the window
	unsigned int get_width() const { return width; }

	// Returns the height of the window
	unsigned int get_height() const { return height; }

	// Returns the type of the window
	WindowType get_window_type() const { return window_type; }

	// Returns the original placement of the window
	WindowPlacement get_window_placement() const { return window_placement; }

private:
	bool update_window();
	struct Impl;
	Impl *impl;
	bool run;
	unsigned int width;
	unsigned int height;
	WindowType window_type;
	WindowPlacement window_placement;
	unsigned int last_tick;
	SDL_Surface *surface;
};

}

#endif