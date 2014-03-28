//_______MESSAGE_SERVER_CPP_______//

#pragma once
#include "nMessageServer.h"

using namespace std;
using namespace sf;

namespace kg
{
	void UdpListenToIncommingMessages( aSwapContainer< NetworkMessage > &container, sf::Uint16 port, std::map< sf::Uint16, bool > &terminators )
	{
		UdpSocket socket;
		socket.bind( port );

		while( !terminators.at( port ) )
		{
			sf::IpAddress remoteIp;
			sf::Uint16 remotePort;
			sf::Packet packet;

			socket.receive( packet, remoteIp, remotePort );

			std::string messageStr;
			packet >> messageStr;
			container.push_back( std::make_pair( kg::nNetworkIdentification( remoteIp, port ), messageStr ) );
		}
	}

	nMessageServer::nMessageServer()
	{ };

	nMessageServer::~nMessageServer()
	{ };

	void nMessageServer::send( const Message &msg, const kg::nNetworkIdentification &to )
	{
		m_swapContainer.push_back( std::make_pair( to, msg.first + KEY_DIVISION_CHAR + msg.second ) );
	};

	const std::vector< NetworkMessage >& nMessageServer::getRecievedMessages( const std::string& key )
	{
		return this->m_recievedMessages[key];
	};

	void nMessageServer::update()
	{
		this->m_recievedMessages.clear();
		this->m_swapContainer.swap();
		auto vec = m_swapContainer.getContent();
		for( auto it = vec.begin(); it != vec.end(); ++it )
		{
			auto vec = aSplitString::function( it->second, KEY_DIVISION_CHAR,
											   aSplitString::operation::REMOVE );
			if( vec.size() != 2 )
				throw std::exception( "MessageServer::update() vec.size!=2" );
			m_recievedMessages[vec.at( NULL )].push_back( std::make_pair( it->first, vec.at( 1 ) ) );
		}

		this->m_answerMessages();
	};

	void nMessageServer::m_answerMessages()
	{ };
};