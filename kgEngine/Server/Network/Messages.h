#pragma once
#include "../stdafx.h"

namespace kg
{
	class ChunkDataRequestAnswer : public nMessage
	{
		std::string m_message;

	public:
		ChunkDataRequestAnswer( const sf::Vector2i& position, const std::array< std::array<int, chunkSizeInTiles>, chunkSizeInTiles >& chunkData );

		virtual std::string getMessage();

		virtual int getID();
	};

	class ConnectionRequestAnswer : public nMessage
	{
		bool m_accepted = false;
		sf::Uint16 m_recievePortOnServer;

	public:
		ConnectionRequestAnswer( sf::Uint16 recievePortOnServer, bool accepted = true );

		virtual std::string getMessage();

		virtual int getID();
	};
}
