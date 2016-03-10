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

				static IPAddress from_octets(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
				{
					return IPAddress((uint32_t)a << 24 | (uint32_t)b << 16 | (uint32_t)c << 8 | (uint32_t)d);
				}

				static IPAddress any() { return IPAddress(0); }
				static IPAddress localhost() { return from_octets(127, 0, 0, 1); }
				
			private:
				uint32_t _address;
			};
		}
	}
}

#endif /* IP_ADDRESS_H */

