#ifndef _COLD_UTIL_ENDIAN_H
#define _COLD_UTIL_ENDIAN_H

namespace endian {

enum endianness {
	BIG = 0x0A,
	LITTLE = 0x0D,
};
extern const endianness value;

void _ch_flip_cpy(char* dest, const char* src, unsigned int len);
inline void flip_cpy(void* dest, const void* src, unsigned int len) {
	_ch_flip_cpy((char*)dest, (char*)src, len);
}
void _ch_memcpy(char* dest, const char* src, unsigned int len);
inline void memcpy(void* dest, const void* src, unsigned int len) {
	_ch_memcpy((char*)dest, (const char*)src, len);
}

template <typename T>
struct Range {
	Range(T* b, T* e)
		: _b(b), _e(e)
	{
	}

	struct Iterator {
		Iterator(T* t) : t(t) { }
		Iterator(T* t, bool b) : t(t), fwd(b) { }
		static Iterator big(T* t) {
			return Iterator(t, true);
		}
		static Iterator little(T* t) {
			Iterator it(t, false);
			--it.t;
			return it;
		}
		void operator++() {
			if (fwd) ++t; else --t;
		}
		void operator--() {
			if (fwd) --t; else ++t;
		}
		void operator++(int) { operator++(); }
		void operator--(int) { operator--(); }
		Iterator operator+(int i) {
			return Iterator(t + i, fwd);
		}
		Iterator operator-(int i) {
			return Iterator(t - i, fwd);
		}
		T& operator*() const {
			return *t;
		}
		T* operator->() const {
			return t;
		}
		bool operator ==(const Iterator& it) {
			return it->t == t;
		}
		bool operator !=(const Iterator& it) {
			return it->t != t;
		}
	private:
		T* t;
		bool fwd;
	};

	Iterator begin() {
		return value == BIG ? Iterator::big(_b) : Iterator::little(_e);
	}
	Iterator end() {
		return Iterator(_e);
	}

private:
	T *_b, *_e;
};



}

#endif