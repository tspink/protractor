#include <server.h>
#include <fd/epoll.h>
#include <fd/net/socket.h>
#include <fd/net/ip-endpoint.h>

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
	Epoll *ep = Epoll::create();
	if (!ep) {
		throw Exception("unable to create epoll");
	}

	Socket *server_socket = Socket::create(AddressFamily::IPv4, SocketType::Stream, ProtocolType::None);
	if (!server_socket) {
		delete ep;
		throw Exception("unable to create server socket");
	}

	IPEndPoint listen_endpoint(IPAddress::any(), 9000);
	server_socket->bind(listen_endpoint);
	server_socket->listen(8);

	ep->add(server_socket, (EpollEvent::EpollEvent)(EpollEvent::IN | EpollEvent::ET));

	while (true) {
		std::list<FileDescriptor *> events;
		if (!ep->wait(events)) {
			delete server_socket;
			delete ep;

			throw Exception("epoll wait failed");
		}

		printf("xxx: %d\n", events.size());
	}

	delete server_socket;
	delete ep;
}

void ProtractorServer::stop()
{
}
