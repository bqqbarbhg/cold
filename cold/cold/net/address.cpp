#include "address.h"
#include <ios>

namespace cold { namespace net {

Address::Address(const impl::ip_t& i, impl::port_t p)
	: port(p), ip(i)
{
}
Address::Address(const impl::ipv4_t& iv4, impl::port_t p)
	: port(p), ip(iv4)
{
}
Address::Address(const impl::ipv6_t& iv6, impl::port_t p)
	: port(p), ip(iv6)
{
}

std::ostream & operator<<(std::ostream & o, const Address& addr) {
	if (addr.ip.is_6) {
		o << '[';
		impl::print_ip(o, addr.ip.v6);
		o << ']';
	} else
		impl::print_ip(o, addr.ip.v4);
	o << ':' << addr.port;
	return o;
}

} }