//_______NETWORK_MANAGER_______//

#pragma once
//Include über <aContainer.h> nicht möglich
#include "../Algorithm/aContainer.h"
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <tuple>
#include <iostream>
#include "nMessage.h"

namespace kg
{

	class nNetworkManager : public pExtendable
	{
		std::map<int, std::shared_ptr<nMessageHandler>> m_messageHandler;

		sf::UdpSocket m_senderSocket;

		// 1= port
		// IPs and Socket sorted by Port
		typedef std::unordered_map<sf::Uint16, std::pair<std::vector<sf::IpAddress>, sf::UdpSocket>> ConnectionContainer;

		// senderIP, recievedPort, message(Handler)ID, message
		typedef aSwapContainer< std::tuple<sf::IpAddress, sf::Uint16, int, std::string> > MessageContainer;

		ConnectionContainer m_connectionContainer;
		MessageContainer m_messageContainer;

		static void m_networkRecieverFunction( ConnectionContainer& connections, MessageContainer& messages );

	public:
		nNetworkManager();

		void addConnection( sf::IpAddress& ip, sf::Uint16 port );

		void sendMessage( std::shared_ptr<nMessage> message, sf::IpAddress& to, sf::Uint16 onPort  );

		void initMessageHandlers();

		void frame( cCore& core );
	};
}
