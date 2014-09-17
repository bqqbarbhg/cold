#include "impl.h"
#include "_sysimpl.h"
#include <sstream>

namespace cold {namespace net { namespace impl {

const unsigned int MAX_CONN = SOMAXCONN;

namespace {
	struct socket_param {
		int af, type, protocol;
		bool ipv6;
	} socket_params[] = {
		{ AF_INET, SOCK_DGRAM, IPPROTO_UDP, false },
		{ AF_INET, SOCK_STREAM, IPPROTO_TCP, false },
		{ AF_INET6, SOCK_DGRAM, IPPROTO_UDP, true },
		{ AF_INET6, SOCK_STREAM, IPPROTO_TCP, true },
	};
	protocol_t v_6[] = {
		UDP_6, TCP_6, UDP_6, TCP_6
	};
}

host_t get_host(const char* name) {
	host_t host = { false };
	hostent *h = gethostbyname(name);
	if (!h) return host;
	host.name = h->h_name;
	switch (h->h_addrtype) {
	case AF_INET:
		host.exists = true;
		for (char** c = h->h_addr_list; *c; c++) {
			host.addrs.push_back(ip_t(ntohl(*(ipv4_t*)*c)));
		}
		break;
	case AF_INET6:
		host.exists = true;
		for (char** c = h->h_addr_list; *c; c++) {
			// TODO(bqq): Endianness
			host.addrs.push_back(ip_t(*(ipv6_t*)*c));
		}
		break;
	}
	return host;
}
void print_ip(std::ostream& o, const ip_t& ip) {
	if (ip.is_6)
		print_ip(o, ip.v6);
	else
		print_ip(o, ip.v4);
}
void print_ip(std::ostream& o, const ipv4_t& ip) {
	std::ios::fmtflags iof(o.flags());
	o << std::dec;
	o << (ip >> 24) << '.' << (ip >> 16 & 0xFF) << '.' << (ip >> 8 & 0xFF) << '.' << (ip & 0xFF);
	o.flags(iof);
}
void print_ip(std::ostream& o, const ipv6_t& ip) {
	std::ios::fmtflags iof(o.flags());
	o << std::hex;
	unsigned int i = 0, b = 0, p = 0, l = 0;
	bool f = true;
	for (const std::uint32_t *u = ip.u32; u != ip.u32 + 4; i++) {
		std::uint_fast16_t v = (f = !f) ? (*u++ >> 16) : (*u & 0xFFFF);
		if (v == 0) {
			if (i - p + 1 > l) {
				b = p;
				l = i - p + 1;
			}
		} else
			p = i + 1;
	}
	l += b;
	i = 0;
	for (const std::uint32_t *u = ip.u32; u != ip.u32 + 4; i++) {
		std::uint_fast16_t v = (f = !f) ? (*u++ >> 16) : (*u & 0xFFFF);
		if (i == b && l != b) {
			o << "::";
		} else if (i < b || i >= l) {
			o << v;
			if (i + 1 < 8 && i + 1 != b)
				o << ":";
		}
	}
	o.flags(iof);
}
protocol_t to_6(protocol_t t) {
	return v_6[t];
}
bool create_socket(socket_t& s, protocol_t p) {
	impl::socket_param *sp = impl::socket_params + p;
	s.h = socket(sp->af, sp->type, sp->protocol);
	s.i6 = sp->ipv6;
	return s.h > 0;
}
bool bind_socket(socket_t& s, port_t port) {
	if (s.i6) {
		 sockaddr_in6 addr;
		 addr.sin6_family = AF_INET6;
		 addr.sin6_addr = in6addr_any;
		 addr.sin6_port = port;
		 return bind(s.h, (const sockaddr*)&addr, sizeof(addr)) >= 0;
	} else {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons((unsigned short) port);
		return bind(s.h, (const sockaddr*)&addr, sizeof(addr)) >= 0;
	}
}
bool listen_socket(socket_t& s, unsigned int max_conn) {
	return listen(s.h, max_conn) == 0;
}
bool connect_socket(socket_t& s, const ip_t& ip, port_t port) {
	if (s.i6) {
		 sockaddr_in6 addr;
		 addr.sin6_family = AF_INET6;
		 std::memcpy(&addr.sin6_addr, ip.v6.u32, sizeof(ip.v6.u32));
		 addr.sin6_port = port;
		 return connect(s.h, (const sockaddr*)&addr, sizeof(addr)) == 0;
	} else {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = ip.v4;
		addr.sin_port = port;
		return connect(s.h, (const sockaddr*)&addr, sizeof(addr)) == 0;
	}
}
bool set_blocking(socket_t& s, bool blocking) {
#if COLD_PLATOFRM == COLDP_WINDOWS
	DWORD nb = blocking ? 0 : 1;
	return ioctlsocket(s.h, FIONBIO, &nb) == 0;
#else
	return fcntl(s.h, F_SETFL, O_NONBLOCK, blocking ? 0 : 1) != -1;
#endif
}
void close_socket(socket_t& s) {
#if COLD_PLATOFRM == COLDP_WINDOWS
	closesocket(s.h);
#else
	close(s.h);
#endif
}

} } }