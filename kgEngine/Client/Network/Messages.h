#pragma once
#include "../stdafx.h"

namespace kg
{
	class ChunkDataRequest : public nMessage
	{
		sf::Vector2i m_position;

	public:
		ChunkDataRequest( const sf::Vector2i& position );

		virtual std::string getMessage();

		virtual int getID();
	};

	class SetTilesRequest : public nMessage
	{
		const std::vector< const sf::Vector2i > m_chunkPosition;
		const std::vector< const sf::Vector2i > m_tilePosition;
		const std::vector< const int > m_tileID;

	public:
		SetTilesRequest( const std::vector< const sf::Vector2i >& chunkPositionInChunks,
						 const std::vector< const sf::Vector2i >& tilePositionRelativeToChunk,
						 const std::vector< const int >& tileID );

		virtual std::string getMessage();

		virtual int getID();
	};

	class ConnectionRequest : public nMessage
	{
		sf::Uint16 m_recievePortOnClient;
		sf::Uint16 m_recievePortOnServer;

	public:
		//recievePortOnClient: port the client listens to
		//recievePortOnServer: port the server 'should' listens to & sendPort linked to recievePortOnClient by server IP
		ConnectionRequest( sf::Uint16 recievePortOnClient, sf::Uint16 recievePortOnServer );

		virtual std::string getMessage();

		virtual int getID();
	};
}
