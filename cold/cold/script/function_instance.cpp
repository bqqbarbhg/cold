#include "function_instance.h"
#include <cold/script/function_definition.h>

namespace cold { namespace script {

FunctionInstance::FunctionInstance(Engine* e, FunctionDefinition* def)
	: Instance(e), definition(def)
{
}

std::string FunctionInstance::repr() const {
	return definition->repr();
}

} }