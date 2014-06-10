//_______MESSAGE_HANDLER_______//

#pragma once
#include <SFML/Network.hpp>
#include <pExtendable.h>


namespace kg
{
	class cCore;

	class nMessage
	{
	public:
		virtual std::string getMessage()=0;

		virtual int getID()=0;

		sf::Packet toPacket()
		{ 
			sf::Packet pack;
			pack << getID() << getMessage();
			return pack;
		};
	};

	class nMessageHandler : public pExtension
	{
	public:
		virtual void handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message )const = 0;

		virtual int getID()const=0;
	};
}
