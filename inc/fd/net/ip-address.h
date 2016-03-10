#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H

#include <protractor.h>

namespace protractor
{
	namespace fd
	{
		namespace net
		{
			class IPAddress
			{
			public:
				IPAddress(uint32_t address) : _address(address) { }
				
				uint32_t address() const { return _address; }
				
			private:
				uint32_t _address;
			};
		}
	}
}

#endif /* IP_ADDRESS_H */

