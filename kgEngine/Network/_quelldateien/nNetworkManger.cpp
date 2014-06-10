#include "../nNetworkManger.h"

void kg::nNetworkManager::m_networkRecieverFunction()
{
	m_mutex.lock();
	for( auto& el : m_connections )
	{
		std::tuple<sf::IpAddress, sf::Uint16, int, std::string> info;
		sf::Packet packet;

		el.second.second.receive( packet, std::get<0>( info ), std::get<1>( info ) );

		packet >> std::get<2>( info ) >> std::get<3>( info );

		m_messageContainer.push_back( info );
	}
	m_mutex.unlock();
}

kg::nNetworkManager::nNetworkManager()
{
	// launch network reciever thread
	// it will run until the application is closed
	std::thread thread;
}