//_______MESSAGE_HANDLERS_SERVER_______//

#pragma once
#include "../stdafx.h"
#include "../Server.h"
#include "Messages.h"

namespace kg
{
	class ChunkDataRequestHandler : public nMessageHandler
	{
	public:

		virtual void handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const;

		virtual int getMessageHandlerID() const;

		virtual std::string info() const;
	};

	class SetTilesRequestHandler : public nMessageHandler
	{
	public:
		virtual void handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const;

		virtual int getMessageHandlerID() const;

		virtual std::string info() const;
	};

	class ConnectionRequestHandler : public nMessageHandler
	{
	public:
		virtual void handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const;

		virtual int getMessageHandlerID() const;

		virtual std::string info() const;
	};
}
