/**
 * src/server.cpp
 *
 * Protractor :: Copyright (C) University of Edinburgh 2016
 * All Rights Reserved
 */
#include <server.h>
#include <fd/epoll.h>
#include <fd/net/socket.h>
#include <fd/net/ip-endpoint.h>

using namespace protractor;
using namespace protractor::fd;
using namespace protractor::fd::net;

/**
 * Constructs a new instance of the Protractor server class.
 */
ProtractorServer::ProtractorServer()
{
	// Create an event to be associated with the 'stop' signal.
	stop_event = Event::create();
}

/**
 * Cleans-up after the Protractor server is done.
 */
ProtractorServer::~ProtractorServer()
{
	// Destroy the stop event object.
	delete stop_event;
}

/**
 * Runs the main Protractor server loop, waiting until told to terminate with
 * the 'stop' signal.
 */
void ProtractorServer::run()
{
	// Create an epoll object, to deal with the event loop.
	Epoll *ep = Epoll::create();
	if (!ep) {
		throw Exception("unable to create epoll");
	}

	// Add the stop event to the epoll event loop, so that we can handle its
	// invocation, and gracefully shutdown.
	ep->add(stop_event, (EpollEventType::EpollEventType)(EpollEventType::IN | EpollEventType::ET));

	// Create a socket that will be the server socket to accept connections
	// on.
	Socket *server_socket = Socket::create(AddressFamily::IPv4, SocketType::Stream, ProtocolType::None);
	if (!server_socket) {
		delete ep;
		throw Exception("unable to create server socket");
	}

	// Add the server socket to the epoll event loop.
	ep->add(server_socket, (EpollEventType::EpollEventType)(EpollEventType::IN));

	// Initialise the server socket with the listening end-point, bind to
	// that address, and begin listening.
	IPEndPoint listen_endpoint(IPAddress::any(), 9000);
	server_socket->bind(listen_endpoint);
	server_socket->listen(8);

	// This is the main server event loop.  Run until instructed to terminate.
	bool terminate = false;
	while (!terminate) {
		// Wait for one or more events to become ready.
		std::list<EpollEvent> events;
		if (!ep->wait(events)) {
			delete server_socket;
			delete ep;

			throw Exception("epoll wait failed");
		}

		// Ignore if no events are ready -- this might happen due to some kind
		// of spurious wake-up.
		if (events.size() == 0) continue;

		// Loop over all the events that are ready this cycle, and deal with
		// them individually.
		for (auto evt : events) {
			if (evt.fd == stop_event) {
				// If the event came from the 'stop' signal, then terminate the loop.
				terminate = true;
				break;
			} else if (evt.fd == server_socket) {
				// If the event came from the 'server' socket, then check to see
				// if was an error, and terminate if so.
				if (evt.err()) {
					terminate = true;
					break;
				}

				// Otherwise, accept a new client socket and handle the result.
				Socket *client_socket = server_socket->accept();
				if (client_socket) {
					try {
						// Add the client socket to the epoll descriptor, so that we
						// start receiving events.
						ep->add(client_socket, (EpollEventType::EpollEventType)(EpollEventType::IN | EpollEventType::HUP | EpollEventType::ERR));
					} catch (Exception& ex) {
						// If there were any issues, delete the accepted socket and continue.
						delete client_socket;
					}
				} else {
					terminate = true;
					break;
				}
			} else {
				// If we got here, then the event came from a client socket.  So, first
				// check to see if there was a hang-up or an error -- and terminate if
				// there was.
				bool socket_error;
				if (evt.hup() || evt.err()) {
					socket_error = true;
				} else {
					// Otherwise, pass on the socket for handling.
					socket_error = !handle_socket((Socket *)evt.fd, evt.in(), evt.out());
				}

				// If an error did occur, remove the socket from the epoll descriptor,
				// and delete it.
				if (socket_error) {
					try {
						ep->remove(evt.fd);
					} catch (Exception& ex) { }

					delete evt.fd;
				}
			}
		}

		// If we've been asked to terminate, break from this loop.
		if (terminate) break;
	}

	// Clean-up by deleting the server socket, and the epoll descriptor.
	// TODO: clean-up any connected clients.
	delete server_socket;
	delete ep;
}

/**
 * Stops the server, by issuing a stop signal.
 */
void ProtractorServer::stop()
{
	// Invoke the 'stop' signal.
	stop_event->invoke();
}

/**
 * Handles activity on a socket.
 * @param skt The socket on which activity occurred.
 * @param read Is the socket ready for reading?
 * @param write Is the socket ready for writing?
 * @return True if the socket was handled without failure, false otherwise.
 */
bool ProtractorServer::handle_socket(fd::net::Socket *skt, bool read, bool write)
{
	// Grab the remote end-point, so we can print-out a nice message.
	// TODO: Don't cast this, and introduce generic printing for end-points.
	const IPEndPoint *ep = (const IPEndPoint *)skt->remote_endpoint();
	printf("handling socket from %s:%d r=%d, w=%d\n", ep->address().to_string().c_str(), ep->port(), read, write);

	// If the event was a read, read the data into a buffer and echo it out
	// to the console.
	if (read) {
		char buffer[1024];
		int rc = skt->read(buffer, 1024);

		// No data?  The connection has been closed, so return false.
		if (rc == 0)
			return false;

		printf("read %u bytes:\n", rc);

		char *p = buffer;
		while (rc-- > 0) {
			printf("%c", *p++);
		}
		printf("\n");
	}

	return true;
}
