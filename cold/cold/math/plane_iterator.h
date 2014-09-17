#ifndef _COLD_MATH_PLANE_ITERATOR_H
#define _COLD_MATH_PLANE_ITERATOR_H

#include <cold/math/plane.h>

namespace cold {
	
	// Struct describing the planes of an object
	template <class T>
	struct PlaneData {
		// Number of planes in the object
		static const int count;

		// Returns the `id`th plane in the object
		Plane get(unsigned int id);
	};

	// Container of the planes describing an object T described
	// by PlaneData<T>
	template <class T>
	struct Planes {
	public:
		struct iterator {
		public:
			iterator (unsigned int c) : ref(0), id(c) { }
			iterator(Planes<T>* r, unsigned int i) : ref(r), id(i) { }
			Plane operator* () const {
				return ref->_data.get(id);
			}
			bool operator!= (const iterator& it) const {
				return it.id != id;
			}
			iterator operator++(int) {
				return iterator(ref, id++);
			}
			iterator operator++() {
				++id;
				return *this;
			}
		private:
			Planes<T>* ref;
			unsigned int id;
		};

		explicit Planes(const PlaneData<T>& data) : _data(data), _end(PlaneData<T>::count) { }

		// Returns the begin iterator to the planes
		iterator begin() { return iterator(this, 0); }

		// Returns the end iterator to the planes
		iterator end() { return _end; }

	private:
		iterator _end;
		PlaneData<T> _data;
	};
}

#endif