#include "socket.h"
#include <cold/net/address.h>

namespace cold { namespace net {

Socket::Socket(Protocol proto) {
	if (!impl::create_socket(_socket, (impl::protocol_t)proto))
		_open = false;
}

Socket::~Socket() {
	if (_open)
		impl::close_socket(_socket);
}

bool Socket::_set_blocking(bool blocking) {
	return impl::set_blocking(_socket, blocking);
}

bool Socket::_connect(const Address& addr) {
	return impl::connect_socket(_socket, addr.ip, addr.port);
}

bool Socket::_listen(unsigned int max_conn) {
	return impl::listen_socket(_socket, max_conn);
}

bool Socket::_bind(unsigned short port) {
	return impl::bind_socket(_socket, port);
}

void Socket::_close() {
	if (!_open) return;
	_open = false;
	impl::close_socket(_socket);
}

Socket::Error Socket::listen(unsigned short port, unsigned int max_conn) {
	if (!_open)
		return ERR_INVALID_SOCKET;
	if (!_bind(port))
		return ERR_COULD_NOT_BIND;
	if (!_listen(max_conn))
		return ERR_COULD_NOT_SET_LISTENING;
	return ERR_NONE;
}
Socket::Error Socket::connect(unsigned short port, const Address& a) {
	if (!_open)
		return ERR_INVALID_SOCKET;
	if (_connect(a))
		return ERR_COULD_NOT_CONNECT;
	return ERR_NONE;
}
Socket::Error Socket::set_blocking(bool blocking) {
	if (!_open)
		return ERR_INVALID_SOCKET;
	if (!_set_blocking(blocking))
		return ERR_COULD_NOT_SET_BLOCKING;
	return ERR_NONE;
}
Socket::Socket(Socket&& s)
	: _open(s._open), _socket(s._socket)
{
	s._open = false;
}
Socket& Socket::operator=(Socket&& s)
{
	if (_open)
		impl::close_socket(_socket);
	_open = s._open;
	_socket = s._socket;
	s._open = false;
	return *this;
}

} }