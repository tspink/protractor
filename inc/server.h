#ifndef SERVER_H
#define SERVER_H

namespace protractor
{
	class ProtractorServer
	{
	public:
		ProtractorServer();
		~ProtractorServer();
		
		void run();
		void stop();
	};
}

#endif /* SERVER_H */

