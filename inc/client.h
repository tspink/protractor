/**
 * inc/client.h
 *
 * Protractor :: Copyright (C) University of Edinburgh 2016
 * All Rights Reserved
 */
#ifndef CLIENT_H
#define CLIENT_H

namespace protractor
{
	namespace fd
	{
		class FileDescriptor;
	}

	class ProtractorClient
	{
	public:
		ProtractorClient(fd::FileDescriptor *transport);

	private:
		fd::FileDescriptor *_transport;
	};
}

#endif /* CLIENT_H */

