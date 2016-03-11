/**
 * src/net/fd/socket.cpp
 *
 * Protractor :: Copyright (C) University of Edinburgh 2016
 * All Rights Reserved
 */
#include <fd/net/socket.h>
#include <sys/socket.h>

using namespace protractor;
using namespace protractor::fd;
using namespace protractor::fd::net;

Socket::Socket(int fd, AddressFamily::AddressFamily family, SocketType::SocketType type, ProtocolType::ProtocolType protocol, const EndPoint *rep)
	: FileDescriptor(fd),
		_family(family),
		_type(type),
		_protocol(protocol),
		_remote_endpoint(rep)
{

}

Socket *Socket::create(AddressFamily::AddressFamily family, SocketType::SocketType type, ProtocolType::ProtocolType protocol)
{
	int fd = ::socket(family, type, protocol);
	if (fd < 0)
		return NULL;

	return new Socket(fd, family, type, protocol, NULL);
}

void Socket::bind(EndPoint& ep)
{
	if (ep.family() != _family)
		throw Exception("end-point not of the correct family");

	socklen_t sa_len;
	struct sockaddr *sa = ep.create_sockaddr(sa_len);
	if (!sa) {
		throw Exception("unable to create sockaddr from endpoint");
	}

	int rc = ::bind(_fd, sa, sa_len);
	ep.free_sockaddr(sa);

	if (rc < 0) {
		throw Exception("unable to bind to socket");
	}
}

void Socket::listen(int max_pending)
{
	if (::listen(_fd, max_pending) < 0) {
		throw Exception("unable to listen on socket");
	}
}

Socket* Socket::accept()
{
	struct sockaddr *sa = (struct sockaddr *)malloc(256);
	socklen_t sa_len = 256;

	int new_fd = ::accept(_fd, sa, &sa_len);
	if (new_fd < 0) {
		free(sa);
		return NULL;
	}

	const EndPoint *rep = EndPoint::from_sockaddr(sa);
	free(sa);

	return new Socket(new_fd, rep->family(), _type, _protocol, rep);
}
