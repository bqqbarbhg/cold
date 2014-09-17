#include "impl.h"
#ifdef COLD_NET_IMPL_WINDOWS
#include "_sysimpl.h"
#include <Windows.h>
#include <cold/util/unique_ptr.h>
#include <cold/util/assert.h>

namespace cold { namespace net {

namespace {
class NetImpl {
public:
	NetImpl() {
		WSAStartup(MAKEWORD(2, 2), &wd);
	}
	~NetImpl() {
		WSACleanup();
	}
	WSADATA wd;
};
UniquePtr<NetImpl> _impl(nullptr);
}

void initialize() {
	COLD_DEBUG_ASSERT(_impl == nullptr);
	_impl = new NetImpl();
}

namespace impl {
	error_t get_last_error() {
		return WSAGetLastError();
	}
}

} }

#endif