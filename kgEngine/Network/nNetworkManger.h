//_______NETWORK_MANAGER_______//

#pragma once
#include <aContainer.h>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <tuple>
#include <SFML/Network.hpp>

namespace kg
{
	class nNetworkManager
	{
		// senderIP, recievedPort, messageTypeID, message
		aSwapContainer< std::tuple<sf::IpAddress, sf::Uint16, int, std::string> > m_messageContainer;

		std::mutex m_mutex;

		// 1= port
		// IPs and Socket sorted by Port
		std::unordered_map<sf::Uint16, std::pair<std::vector<sf::IpAddress>, sf::UdpSocket>> m_connections;

		void m_networkRecieverFunction();

	public:
		nNetworkManager();

		//virtual void handleMessages()const = 0;
	};
}