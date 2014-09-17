#include "enums.h"

#include <cold/render/types.h>

namespace cold {
	unsigned int get_data_type_size(DataType t) {
		switch (t) {
			case DATA_BYTE: return sizeof(c_byte);
			case DATA_UNSIGNED_BYTE: return sizeof(c_ubyte);
			case DATA_SHORT: return sizeof(c_short);
			case DATA_UNSIGNED_SHORT: return sizeof(c_ushort);
			case DATA_INT: return sizeof(c_int);
			case DATA_UNSIGNED_INT: return sizeof(c_uint);
			case DATA_FLOAT: return sizeof(c_float);
			case DATA_DOUBLE: return sizeof(c_double);
		}
		return 0;
	}
}