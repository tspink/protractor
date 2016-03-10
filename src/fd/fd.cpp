#include <fd/fd.h>

namespace std {
#include <unistd.h>
}

using namespace protractor;
using namespace protractor::fd;

FileDescriptor::FileDescriptor(int fd) : _fd(fd)
{

}

void FileDescriptor::close()
{
	std::close(_fd);
}

FileDescriptor::~FileDescriptor()
{
	this->close();
}
