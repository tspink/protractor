#include <server.h>
#include <fd/net/socket.h>

using namespace protractor;
using namespace protractor::fd;
using namespace protractor::fd::net;

ProtractorServer::ProtractorServer()
{

}

ProtractorServer::~ProtractorServer()
{

}

void ProtractorServer::run()
{
	Socket *server_socket = Socket::create(AddressFamily::IPv4, SocketType::Stream, ProtocolType::None);
	if (!server_socket)
		throw Exception("unable to create server socket");
	
	delete server_socket;
}

void ProtractorServer::stop()
{
}
