//_______NETWORK_MANAGER_______//

#pragma once
#include <aContainer.h>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <tuple>
#include <iostream>
#include <SFML/Network.hpp>

namespace kg
{

	class nNetworkManager
	{

		typedef std::unordered_map<sf::Uint16, std::pair<std::vector<sf::IpAddress>, sf::UdpSocket>> ConnectionContainer;
		typedef aSwapContainer< std::tuple<sf::IpAddress, sf::Uint16, int, std::string> > MessageContainer;

		// 1= port
		// IPs and Socket sorted by Port
		ConnectionContainer m_connectionContainer;

		// senderIP, recievedPort, messageTypeID, message
		MessageContainer m_messageContainer;

		static void m_networkRecieverFunction( ConnectionContainer& connections, MessageContainer& messages );

	public:
		nNetworkManager();

		//virtual void handleMessages()const = 0;
	};
}