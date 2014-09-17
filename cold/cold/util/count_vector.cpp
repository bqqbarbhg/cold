#include "count_vector.h"
#include <algorithm>

namespace cold {

CountVector::CountVector(unsigned int el_size)
	: RawVector(0)
	, elem_size(el_size)
	, count(0)
{
}
CountVector::CountVector(const CountVector& cv)
	: RawVector(cv)
	, count(cv.count)
	, elem_size(cv.elem_size)
{
}
CountVector& CountVector::operator=(CountVector cv) {
	std::swap(*this, cv);
	return *this;
}

}