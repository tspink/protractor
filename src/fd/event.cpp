/**
 * src/fd/event.cpp
 *
 * Protractor :: Copyright (C) University of Edinburgh 2016
 * All Rights Reserved
 */
#include <fd/event.h>
#include <sys/eventfd.h>
#include <unistd.h>

using namespace protractor;
using namespace protractor::fd;

/**
 * Creates an new eventfd wrapper, for the given fd.
 * @param fd
 */
Event::Event(int fd) : FileDescriptor(fd)
{

}

/**
 * Performs the creation of the eventfd wrapper.
 * @return An Event object that represents a new eventfd, or NULL if an error
 * occurred.
 */
Event *Event::create()
{
	int fd = eventfd(0, 0);
	if (fd < 0)
		return NULL;

	return new Event(fd);
}

/**
 * Invokes the eventfd.
 */
void Event::invoke()
{
	uint64_t v = 1;
	write(&v, sizeof(v));
}
