#ifndef _COLD_PLATFORM_IO_H
#define _COLD_PLATFORM_IO_H

#include <string>

namespace cold {

// Reads a whole file into a string
// file: Path to the file to read
std::string read_file_string(const char* file);

}

#endif