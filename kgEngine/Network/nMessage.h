//_______MESSAGE_HANDLER_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class cCore;
	class nNetworkManager;

	class NETWORK_API nMessage
	{
	public:
		virtual std::string getMessage() = 0;

		virtual int getID() = 0;

		sf::Packet toPacket()
		{
			sf::Packet pack;
			pack << getID() << getMessage();
			return pack;
		};
	};

	class NETWORK_API nMessageHandler : public pExtension
	{
	public:
		virtual ~nMessageHandler()
		{ };

		virtual void handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message )const = 0;

		virtual int getMessageHandlerID()const = 0;
	};
}
