//_______MESSAGE_HANDLERS_CLIENT_______//

#pragma once
#include "../stdafx.h"
#include "../Client.h"
#include "Messages.h"

namespace kg
{
	class ChunkDataRequestAnswerHandler : public nMessageHandler
	{
	public:

		virtual void handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const;

		virtual int getMessageHandlerID() const;

		virtual std::string info() const;
	};

	class ConnectionRequestAnswerHandler : public nMessageHandler
	{
	public:
		virtual void handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const;

		virtual int getMessageHandlerID() const;

		virtual std::string info() const;
	};
}
