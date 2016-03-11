/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   endpoint.h
 * Author: s0457958
 *
 * Created on 10 March 2016, 16:39
 */

#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <fd/net/types.h>

#include <sys/socket.h>

namespace protractor
{
	namespace fd
	{
		namespace net
		{
			class EndPoint
			{
			public:
				EndPoint(AddressFamily::AddressFamily family);
				virtual ~EndPoint();

				AddressFamily::AddressFamily family() const { return _family; }

				virtual struct sockaddr *create_sockaddr(socklen_t& len) = 0;
				virtual void free_sockaddr(struct sockaddr *sa) = 0;

				static const EndPoint *from_sockaddr(const struct sockaddr *sa);

			private:
				AddressFamily::AddressFamily _family;
			};
		}
	}
}

#endif /* ENDPOINT_H */

