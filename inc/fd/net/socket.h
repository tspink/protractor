/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   socket-fd.h
 * Author: s0457958
 *
 * Created on 10 March 2016, 16:17
 */

#ifndef SOCKET_FD_H
#define SOCKET_FD_H

#include <fd/fd.h>
#include <fd/net/types.h>
#include <fd/net/endpoint.h>

namespace protractor
{
	namespace fd
	{
		namespace net
		{
			class Socket : public FileDescriptor
			{
			public:
				static Socket *create(AddressFamily::AddressFamily family, SocketType::SocketType type, ProtocolType::ProtocolType protocol);

				void bind(EndPoint& ep);
				void listen(int max_pending);

			private:
				Socket(int fd, AddressFamily::AddressFamily family, SocketType::SocketType type, ProtocolType::ProtocolType protocol);

				AddressFamily::AddressFamily _family;
				SocketType::SocketType _type;
				ProtocolType::ProtocolType _protocol;
			};
		}
	}
}

#endif /* SOCKET_FD_H */

