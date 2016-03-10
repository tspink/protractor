#include <fd/net/ip-endpoint.h>
#include <malloc.h>

using namespace protractor::fd::net;

std::sockaddr *IPEndPoint::create_sockaddr(std::socklen_t& len)
{
	std::sockaddr *sa = malloc(sizeof(int));
	return sa;
}

void IPEndPoint::free_sockaddr(std::sockaddr *sa)
{
	free(sa);
}
