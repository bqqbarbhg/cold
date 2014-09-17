#ifndef _COLD_PLATFORM_PLATFORM_H
#define _COLD_PLATFORM_PLATFORM_H

// Supported compilation platforms
enum ColdPlatform {
	// Windows
	COLDP_WINDOWS = 1,
	// Unix
	COLDP_UNIX = 2,
	// Mac
	COLDP_MAC = 3,
};

#ifdef _WIN32
// Current platform
// Use #if COLD_PLATFORM == COLDP_WINDOWS
 #define COLD_PLATFORM COLDP_WINDOWS
#else
 #error "Unsupported platform"
#endif

#endif