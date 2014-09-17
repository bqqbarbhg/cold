#include "instance.h"

namespace cold { namespace script {

Instance::Instance(Engine *e)
	: mark(false), unmanaged_ptr_count(0), engine(e)
{
}

} }