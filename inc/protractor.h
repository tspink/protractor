#ifndef __PROTRACTOR_H__
#define __PROTRACTOR_H__

#include <stddef.h>
#include <stdint.h>

#include <string>

namespace protractor
{
	class Exception
	{
	public:
		Exception(std::string message) : _message(message) { }

		std::string message() const { return _message; }

	private:
		std::string _message;
	};

	class NotImplementedException : public Exception
	{
	public:
		NotImplementedException() : Exception("not implemented") { }
	};
}

#endif
