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

#include <sys/types.h>
#include <sys/socket.h>

namespace protractor
{
	namespace fd
	{
		class Socket : public FileDescriptor
		{
		public:
			enum AddressFamily
			{
				Unix = AF_UNIX,
				IPv4 = AF_INET,
				IPv6 = AF_INET6,
			};

			enum SocketType
			{
				Stream = SOCK_STREAM,
				Datagram = SOCK_DGRAM,
				Raw = SOCK_RAW,
			};

			enum ProtocolType
			{
				None = 0,
			};

			static Socket *create(AddressFamily family, SocketType type, ProtocolType protocol);

		private:
			Socket(int fd);
		};
	}
}

#endif /* SOCKET_FD_H */

