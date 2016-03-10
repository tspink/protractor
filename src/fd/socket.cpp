#include <fd/socket-fd.h>

using namespace protractor;
using namespace protractor::fd;

Socket::Socket(int fd) : FileDescriptor(fd)
{
	
}

Socket *Socket::create(AddressFamily family, SocketType type, ProtocolType protocol)
{
	int fd = socket(family, type, protocol);
	if (fd < 0)
		return NULL;
	
	return new Socket(fd);
}
