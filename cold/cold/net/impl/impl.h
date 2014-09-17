#ifndef _COLD_NET_IMPL_IMPL_H
#define _COLD_NET_IMPL_IMPL_H

#include <cold/platform/platform.h>
#include <string>
#include <cstdint>
#include <vector>
#include <ostream>

#if COLD_PLATFORM == COLDP_WINDOWS
 #include "win32.h"
#else
 #error "Unsupported platform for networking"
#endif

namespace cold { namespace net { namespace impl {

enum protocol_t {
	UDP,
	TCP,
	UDP_6,
	TCP_6,
};

typedef struct {
	socket_handle_t h;
	bool i6;
} socket_t;
typedef std::uint32_t ipv4_t;
typedef struct {
	std::uint32_t u32[4];
} ipv6_t;
struct ip_t {
	ip_t(ipv4_t i)
		: is_6(false), v4(i) {}
	ip_t(ipv6_t i)
		: is_6(true), v6(i) {}
	bool is_6;
	union {
		ipv4_t v4;
		ipv6_t v6;
	};
};
struct host_t {
	bool exists;
	std::string name;
	std::vector<ip_t> addrs;
};
typedef unsigned short port_t;

extern const unsigned int MAX_CONN;
void print_ip(std::ostream& o, const ipv4_t& ip);
void print_ip(std::ostream& o, const ipv6_t& ip);
void print_ip(std::ostream& o, const ip_t& ip);
host_t get_host(const char* name);
protocol_t to_6(protocol_t t);
bool create_socket(socket_t& s, protocol_t p);
bool bind_socket(socket_t& s, port_t port);
bool listen_socket(socket_t& s, unsigned int max_conn);
bool connect_socket(socket_t& s, const ip_t& ip, port_t port);
bool set_blocking(socket_t& s, bool blocking);
void close_socket(socket_t& s);
error_t get_last_error();

} } }


#endif