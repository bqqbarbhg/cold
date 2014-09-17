#ifndef _COLD_BASE_OS_H
#define _COLD_BASE_OS_H

namespace cold {
namespace os {

// Visual style of a message box
enum MessageBoxType {
	// Error, X in a red circle in Windows
	MBOX_ERROR,
	// Warning, yellow triangle with an ! in Windows
	MBOX_WARNING,
	// Information, i sign on Windows
	MBOX_INFORMATION,
};

// Displays a message box in the current window manager
// title: Title (caption) of the message box
// text: Text inside the message box
// type: Style of the message box (may be ignored depending on the os)
void message_box(const char* title, const char* text, MessageBoxType type);

// Returns the height of the current monitor
unsigned int get_screen_width();

// Returns the width of the current monitor
unsigned int get_screen_height();

}
}

#endif