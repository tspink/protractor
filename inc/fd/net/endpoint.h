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

namespace std
{
#include <sys/socket.h>
}

namespace protractor
{
	namespace fd
	{
		namespace net
		{
			class EndPoint
			{
			public:
				EndPoint(AddressFamily::AddressFamily family) : _family(family) { }
				
				AddressFamily::AddressFamily family() const { return _family; }
				
				virtual std::sockaddr *create_sockaddr(std::socklen_t& len) = 0;
				virtual void free_sockaddr(std::sockaddr *) = 0;
				
			private:
				AddressFamily::AddressFamily _family;
			};
		}
	}
}

#endif /* ENDPOINT_H */

