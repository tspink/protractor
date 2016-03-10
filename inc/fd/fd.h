#ifndef FD_H
#define FD_H

#include <protractor.h>

namespace protractor
{
	namespace fd {
		class FileDescriptor
		{
		public:
			~FileDescriptor();
			void close();

		protected:
			FileDescriptor(int fd);		
			int _fd;
		};
	}
}

#endif /* FD_H */
