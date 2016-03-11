/**
 * src/fd/net/endpoint.cpp
 *
 * Protractor :: Copyright (C) University of Edinburgh 2016
 * All Rights Reserved
 */
#include <fd/net/ip-endpoint.h>
#include <malloc.h>
#include <netinet/in.h>

using namespace protractor::fd::net;

EndPoint::EndPoint(AddressFamily::AddressFamily af) : _family(af) { }

EndPoint::~EndPoint() {
}

const EndPoint *EndPoint::from_sockaddr(const struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		const struct sockaddr_in *sa_in = (const struct sockaddr_in *)sa;
		return new IPEndPoint(IPAddress(ntohl(sa_in->sin_addr.s_addr)), ntohs(sa_in->sin_port));
	} else {
		return NULL;
	}
}


IPEndPoint::IPEndPoint(const IPAddress& addr, int port) : EndPoint(AddressFamily::IPv4), _addr(addr), _port(port)
{

}

IPEndPoint::~IPEndPoint()
{
}

struct sockaddr *IPEndPoint::create_sockaddr(socklen_t& len)
{
	struct sockaddr_in *sa = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

	sa->sin_family = AF_INET;
	sa->sin_port = htons(_port);
	sa->sin_addr.s_addr = htonl(_addr.address());

	return (struct sockaddr *)sa;
}

void IPEndPoint::free_sockaddr(struct sockaddr *sa)
{
	free(sa);
}
