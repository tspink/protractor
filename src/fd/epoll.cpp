#include <fd/epoll.h>
#include <sys/epoll.h>

using namespace protractor;
using namespace protractor::fd;

Epoll *Epoll::create()
{
	int fd = epoll_create1(0);
	if (fd < 0)
		return NULL;

	return new Epoll(fd);
}

Epoll::Epoll(int fd) : FileDescriptor(fd)
{

}

void Epoll::add(FileDescriptor* fd, EpollEventType::EpollEventType events)
{
	struct epoll_event evt;
	evt.data.ptr = fd;
	evt.events = (uint32_t)events;

	if (epoll_ctl(_fd, EPOLL_CTL_ADD, fd->fd(), &evt) < 0)
		throw Exception("unable to add file descriptor");
}

void Epoll::remove(FileDescriptor* fd)
{
	if (epoll_ctl(_fd, EPOLL_CTL_DEL, fd->fd(), NULL) < 0)
		throw Exception("unable to remove file descriptor");
}

bool Epoll::wait(std::list<EpollEvent>& events, int max_events, int timeout)
{
	struct epoll_event evts[max_events];

	int count = epoll_wait(_fd, evts, max_events, timeout);
	if (count < 0) {
		if (errno == EINTR)
			return true;
		return false;
	}

	for (int i = 0; i < count; i++) {
		events.push_back({
			(FileDescriptor *)evts[i].data.ptr,
			(EpollEventType::EpollEventType)evts[i].events
		});
	}

	return true;
}
