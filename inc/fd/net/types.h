/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   types.h
 * Author: s0457958
 *
 * Created on 10 March 2016, 16:49
 */

#ifndef TYPES_H
#define TYPES_H

namespace protractor
{
	namespace fd
	{
		namespace net
		{
			namespace AddressFamily
			{
				enum AddressFamily
				{
					Unix = 1,
					IPv4 = 2,
					IPv6 = 10,
				};
			}
			
			namespace SocketType
			{
				enum SocketType
				{
					Stream = 1,
					Datagram = 2,
					Raw = 3,
				};
			}
			
			namespace ProtocolType
			{
				enum ProtocolType
				{
					None = 0,
				};
			}
		}
	}
}

#endif /* TYPES_H */

