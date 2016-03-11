#include <server.h>
#include <fd/epoll.h>
#include <fd/net/socket.h>
#include <fd/net/ip-endpoint.h>

using namespace protractor;
using namespace protractor::fd;
using namespace protractor::fd::net;

ProtractorServer::ProtractorServer()
{
	stop_event = Event::create();
}

ProtractorServer::~ProtractorServer()
{
	delete stop_event;
}

void ProtractorServer::run()
{
	Epoll *ep = Epoll::create();
	if (!ep) {
		throw Exception("unable to create epoll");
	}

	ep->add(stop_event, (EpollEventType::EpollEventType)(EpollEventType::IN | EpollEventType::ET));

	Socket *server_socket = Socket::create(AddressFamily::IPv4, SocketType::Stream, ProtocolType::None);
	if (!server_socket) {
		delete ep;
		throw Exception("unable to create server socket");
	}

	IPEndPoint listen_endpoint(IPAddress::any(), 9000);
	server_socket->bind(listen_endpoint);
	server_socket->listen(8);

	ep->add(server_socket, (EpollEventType::EpollEventType)(EpollEventType::IN));

	bool terminate = false;
	while (true) {
		std::list<EpollEvent> events;
		if (!ep->wait(events)) {
			delete server_socket;
			delete ep;

			throw Exception("epoll wait failed");
		}

		for (auto evt : events) {
			if (evt.fd == stop_event) {
				terminate = true;
				break;
			} else if (evt.fd == server_socket) {
				Socket *client_socket = server_socket->accept();
				if (client_socket) {
					try {
						ep->add(client_socket, (EpollEventType::EpollEventType)(EpollEventType::IN | EpollEventType::HUP | EpollEventType::ERR));
					} catch (Exception& ex) {
						delete client_socket;
					}
				} else {
					terminate = true;
					break;
				}
			} else {
				bool socket_error;

				if (evt.hup() || evt.err()) {
					socket_error = true;
				} else {
					socket_error = !handle_socket((Socket *)evt.fd, evt.in(), evt.out());
				}

				if (socket_error) {
					try {
						ep->remove(evt.fd);
					} catch (Exception& ex) { }

					delete evt.fd;
				}
			}
		}

		if (terminate) break;
	}

	delete server_socket;
	delete ep;
}

void ProtractorServer::stop()
{
	stop_event->invoke();
}

bool ProtractorServer::handle_socket(fd::net::Socket *skt, bool read, bool write)
{
	const IPEndPoint *ep = (const IPEndPoint *)skt->remote_endpoint();

	printf("handling socket from %s:%d r=%d, w=%d\n", ep->address().to_string().c_str(), ep->port(), read, write);

	if (read) {
		char buffer[1024];
		int rc = skt->read(buffer, 1024);

		if (rc == 0)
			return false;

		printf("read %lu bytes\n", rc);
	}

	return true;
}
