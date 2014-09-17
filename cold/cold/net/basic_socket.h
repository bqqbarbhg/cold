#ifndef _COLD_NET_BASIC_SOCKET_H
#define _COLD_NET_BASIC_SOCKET_H

#include <cold/net/socket.h>

namespace cold { namespace net {

class BasicSocket : Socket {
	BasicSocket(Protocol proto, unsigned int port)
		: Socket(proto)
	{
		if (!_bind(port)) {
			_close(); return;
		}
		if (!_set_blocking(false)) {
			_close(); return;
		}
	}
};

} }

#endif