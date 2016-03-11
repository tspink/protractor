/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ip-endpoint.h
 * Author: s0457958
 *
 * Created on 10 March 2016, 16:40
 */

#ifndef IP_ENDPOINT_H
#define IP_ENDPOINT_H

#include <fd/net/endpoint.h>
#include <fd/net/ip-address.h>

namespace protractor
{
	namespace fd
	{
		namespace net
		{
			class IPEndPoint : public EndPoint
			{
			public:
				IPEndPoint(const IPAddress& addr, int port);
				~IPEndPoint();

				const IPAddress& address() const { return _addr; }
				int port() const { return _port; }

				virtual struct sockaddr *create_sockaddr(socklen_t& len) override;
				virtual void free_sockaddr(struct sockaddr *sa) override;

			private:
				const IPAddress _addr;
				int _port;
			};
		}
	}
}

#endif /* IP_ENDPOINT_H */

