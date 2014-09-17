#ifndef _COLD_NET_SOCKET_H
#define _COLD_NET_SOCKET_H

#include <cold/net/impl/impl.h>

namespace cold { namespace net {

class Address;
class Socket {
public:
	enum Protocol {
		UDP = net::impl::UDP,
		TCP = net::impl::TCP,
		UDP_6 = net::impl::UDP_6,
		TCP_6 = net::impl::TCP_6,
	};
	enum Error {
		ERR_NONE,
		ERR_INVALID_SOCKET,
		ERR_COULD_NOT_CREATE,
		ERR_COULD_NOT_BIND,
		ERR_COULD_NOT_SET_BLOCKING,
		ERR_COULD_NOT_SET_LISTENING,
		ERR_COULD_NOT_CONNECT,
	};

	Socket(Protocol proto);
	~Socket();

	Socket(Socket&& s);
	Socket& operator=(Socket&& s);

	Error listen(unsigned short port, unsigned int max_conn=impl::MAX_CONN);
	Error connect(unsigned short port, const Address& addr);
	Error set_blocking(bool blocking);

	bool is_open() const { return _open; }
protected:
	bool _set_blocking(bool blocking);
	bool _connect(const Address& addr);
	bool _listen(unsigned int max_conn=impl::MAX_CONN);
	bool _bind(unsigned short port);
	void _close();
	
	bool _open;
private:
	Socket(const Socket&& s);
	Socket& operator=(const Socket&& s);
	net::impl::socket_t _socket;
};

} }

#endif