#ifndef EPOLL_H
#define EPOLL_H

#include <fd/fd.h>
#include <list>

namespace protractor
{
	namespace fd
	{
		namespace EpollEvent
		{
			enum EpollEvent
			{
				IN = 0x001,
				PRI = 0x002,
				OUT = 0x004,
				RDNORM = 0x040,
				RDBAND = 0x080,
				WRNORM = 0x100,
				WRBAND = 0x200,
				MSG = 0x400,
				ERR = 0x008,
				HUP = 0x010,
				RDHUP = 0x2000,
				WAKEUP = 1u << 29,
				ONESHOT = 1u << 30,
				ET = 1u << 31
			};
		}

		class Epoll : public FileDescriptor
		{
		public:
			static Epoll *create();

			void add(FileDescriptor *fd, EpollEvent::EpollEvent events);
			void remove(FileDescriptor *fd);
			bool wait(std::list<FileDescriptor *>& events, int max_events = 24, int timeout = -1);

		private:
			Epoll(int fd);
		};
	}
}

#endif /* EPOLL_H */

