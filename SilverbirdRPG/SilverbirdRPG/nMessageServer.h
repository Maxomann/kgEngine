//_______MESSAGE_SERVER_H_______//

#pragma once
#include "stdafx.h"
#include "aContainer.h"
#include "aSingelton.h"
#include "nNetworkIdentification.h"
#include "aString.h"

namespace kg
{
	typedef std::pair<std::string, std::string> Message;
	//first=Key, second=Message
	typedef std::pair<nNetworkIdentification, std::string> NetworkMessage;
	//first=NId, second=Message wit Key (KEY_DEVISION_CHAR)

	/*runs while terminator is false*/
	void UdpListenToIncommingMessages( aSwapContainer< NetworkMessage > &container, sf::Uint16 port, std::map< sf::Uint16, bool > &terminators );

#pragma message("warning: rewrite MessageServer")
	//You MUST NOT create more than one instance of this class in your programm
	class nMessageServer
	{
	public:
		nMessageServer();
		~nMessageServer();

		void send( const Message& message, const kg::nNetworkIdentification &to );

		const std::vector< NetworkMessage >&					getRecievedMessages(
			const std::string& key );

		//Todo: sf::Uint16 getPing( const kg::NetworkIdentification &to );

		void update();

		static const sf::Uint16									STANDART_MESSAGE_PORT = 42000;
		static const char										KEY_DIVISION_CHAR = '~';

	private:
		std::map<std::string, std::vector< NetworkMessage >	>	m_recievedMessages;
		kg::aSwapContainer< NetworkMessage >					m_swapContainer;

		void													m_answerMessages();
	};
};//kg