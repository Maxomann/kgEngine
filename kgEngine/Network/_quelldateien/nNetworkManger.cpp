#include "../nNetworkManger.h"

static std::mutex networkMutex;

void kg::nNetworkManager::m_networkRecieverFunction( ConnectionContainer& connections, MessageContainer& messages )
{
	while( true )
	{
		//std::cout << "Ich empfange Narchichten" << std::endl; //// to test if the thread works
		networkMutex.lock();
		for( auto& el : connections )
		{
			std::tuple<sf::IpAddress, sf::Uint16, int, std::string> info;
			sf::Packet packet;

			if( el.second.second.receive( packet, std::get<0>( info ), std::get<1>( info ) ) )
			{
				//erfolg
			}
			else
			{
				//fehler
			}

			packet >> std::get<2>( info ) >> std::get<3>( info );

			messages.push_back( info );
		}
		networkMutex.unlock();
	}
}

kg::nNetworkManager::nNetworkManager()
{
	// launch network reciever thread
	// it will run until the application is closed
	std::thread thread(&m_networkRecieverFunction, std::ref(m_connectionContainer), std::ref(m_messageContainer));
	thread.detach();
}