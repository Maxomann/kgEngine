//_______NETWORK_MANAGER_______//

#pragma once
#include "nMessage.h"
#include "stdafx.h"

namespace kg
{
	class nNetworkManager : public pExtendable
	{
		bool m_terminateNetworkThread = false;

		std::map<int, std::shared_ptr<nMessageHandler>> m_messageHandler;

		// 1= recievePort
		// pair: <IPs, answerPort> and Socket sorted by recievePort
		typedef std::unordered_map < sf::Uint16, std::pair < std::vector<std::pair<sf::IpAddress, sf::Uint16>>, sf::UdpSocket >> ConnectionContainer;

		// senderIP, recievedPort, message(Handler)ID, message
		typedef aSwapContainer< std::tuple<sf::IpAddress, sf::Uint16, int, std::string> > MessageContainer;

		ConnectionContainer m_connectionContainer;
		MessageContainer m_messageContainer;

		static void m_networkRecieverFunction( ConnectionContainer& connections, MessageContainer& messages, bool& shouldTerminate );

	public:
		NETWORK_API nNetworkManager();
		NETWORK_API ~nNetworkManager();

		//One ip MUST NOT be connected on more than one port (because of spread)
		NETWORK_API void addConnection( const sf::IpAddress& ip, sf::Uint16 recievePort, sf::Uint16 answerPort );

		NETWORK_API void sendMessage( std::shared_ptr<nMessage> message, const sf::IpAddress& to, sf::Uint16 onPort );

		//sends the message to everyone who is connected
		NETWORK_API void spreadMessage( std::shared_ptr<nMessage> message );

		//the Handlers must have been added to the class by pExtension before calling this function
		NETWORK_API void initMessageHandlers();

		NETWORK_API void frame( cCore& core );

		NETWORK_API virtual void initExtensions( pPluginManager& pluginManager );

		NETWORK_API sf::Uint16 getAnswerPort(sf::IpAddress forIp, sf::Uint16 recievedOnPort);
	};
}
