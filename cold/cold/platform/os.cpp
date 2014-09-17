#include "os.h"
#include <Windows.h>

namespace cold { namespace os {

void message_box(const char* title, const char* text, MessageBoxType mbt) {
	UINT ut = MB_OK;
	switch (mbt) {
	case MBOX_ERROR: ut |= MB_ICONERROR; break;
	case MBOX_WARNING: ut |= MB_ICONWARNING; break;
	case MBOX_INFORMATION: ut |= MB_ICONINFORMATION; break;
	}
	MessageBox(NULL, text, title, ut);
}


unsigned int get_screen_width() {
	return GetSystemMetrics(SM_CXSCREEN);
}

unsigned int get_screen_height() {
	return GetSystemMetrics(SM_CYSCREEN);
}

} }