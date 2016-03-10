#include <fd/net/ip-endpoint.h>
#include <malloc.h>
#include <netinet/in.h>

using namespace protractor::fd::net;

EndPoint::EndPoint(AddressFamily::AddressFamily af) : _family(af) { }

EndPoint::~EndPoint() { }

IPEndPoint::IPEndPoint(IPAddress addr, int port) : EndPoint(AddressFamily::IPv4), _addr(addr), _port(port)
{

}

IPEndPoint::~IPEndPoint()
{
}

struct sockaddr *IPEndPoint::create_sockaddr(socklen_t& len)
{
	struct sockaddr_in *sa = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

	//sa->

	return (struct sockaddr *)sa;
}

void IPEndPoint::free_sockaddr(struct sockaddr *sa)
{
	free(sa);
}
