/**
 * inc/server.h
 *
 * Protractor :: Copyright (C) University of Edinburgh 2016
 * All Rights Reserved
 */
#ifndef SERVER_H
#define SERVER_H

#include <fd/event.h>
#include <list>

namespace protractor
{
	namespace fd
	{
		namespace net
		{
			class Socket;
		}
	}

	class ProtractorServer
	{
	public:
		ProtractorServer();
		~ProtractorServer();

		void run();
		void stop();

	private:
		fd::Event *stop_event;
		std::list<fd::net::Socket *> clients;

		bool handle_socket(fd::net::Socket *skt, bool read, bool write);
	};
}

#endif /* SERVER_H */

