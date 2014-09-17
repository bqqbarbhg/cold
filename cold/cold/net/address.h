#ifndef _COLD_NET_ADDRESS_H
#define _COLD_NET_ADDRESS_H

#include <cold/net/impl/impl.h>
#include <ostream>

namespace cold { namespace net {

class Address {
public:
	Address(const impl::ip_t& ip, impl::port_t port);
	Address(const impl::ipv4_t& iv4, impl::port_t port);
	Address(const impl::ipv6_t& iv6, impl::port_t port);

	impl::ip_t ip;
	impl::port_t port;
};
std::ostream & operator<<(std::ostream & o, const Address& addr);

} }

#endif