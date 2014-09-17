#if 0
#include <cstdio>
#include <iostream>
#include <cold/net/socket.h>
#include <cold/net/net.h>
#include <cold/net/address.h>

int main(int argc, char** argv) {
	using namespace cold::net;
	using namespace std;

	initialize();

	char buffer[2048];
	char *cptr;
	while (true) {
		cptr = buffer;
		cout << "> ";
		while ((*cptr++ = getchar()) != '\n')
			;
		cptr[-1] = 0;
		impl::host_t host = impl::get_host(buffer);
		if (host.exists) {
			cout << host.name << endl;
			for (const auto& ip : host.addrs) {
				cout << " ";
				impl::print_ip(cout, ip);
				cout << endl;
			}
		} else {
			cout << "Could not find host." << endl;
		}
	}
}

#endif