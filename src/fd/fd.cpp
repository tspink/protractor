#include <fd/fd.h>
#include <unistd.h>

using namespace protractor;
using namespace protractor::fd;

FileDescriptor::FileDescriptor(int fd) : _fd(fd)
{

}

int FileDescriptor::read(void* buffer, size_t size)
{
	return ::read(_fd, buffer, size);
}

int FileDescriptor::write(void* buffer, size_t size)
{
	return ::write(_fd, buffer, size);
}


void FileDescriptor::close()
{
	::close(_fd);
}

FileDescriptor::~FileDescriptor()
{
	this->close();
}
