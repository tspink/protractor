#include <fd/event.h>
#include <sys/eventfd.h>
#include <unistd.h>

using namespace protractor;
using namespace protractor::fd;

Event::Event(int fd) : FileDescriptor(fd)
{

}

Event *Event::create()
{
	int fd = eventfd(0, 0);
	if (fd < 0)
		return NULL;

	return new Event(fd);
}

void Event::invoke()
{
	uint64_t v = 1;
	write(&v, sizeof(v));
}
