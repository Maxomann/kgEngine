#pragma once
#include "../stdafx.h"

namespace kg
{
	class ChunkDataRequest : public nMessage
	{
		sf::Vector2i m_position;

	public:
		ChunkDataRequest( const sf::Vector2i& position )
			:m_position( position )
		{ }

		virtual std::string getMessage()
		{
			return std::to_string( m_position.x ) + standartSplitChar + std::to_string( m_position.y );
		}

		virtual int getID()
		{
			return MESSAGE_ID_CLIENT::CHUNK_DATA_REQUEST;
		}
	};

	class SetTilesRequest : public nMessage
	{
		const std::vector< const sf::Vector2i > m_chunkPosition;
		const std::vector< const sf::Vector2i > m_tilePosition;
		const std::vector< const int > m_tileID;

	public:
		SetTilesRequest( const std::vector< const sf::Vector2i >& chunkPositionInChunks,
						 const std::vector< const sf::Vector2i >& tilePositionRelativeToChunk,
						 const std::vector< const int >& tileID )
			:m_chunkPosition( chunkPositionInChunks ),
			m_tilePosition( tilePositionRelativeToChunk ),
			m_tileID( tileID )
		{ }

		virtual std::string getMessage()
		{
			std::string message;

// 			return std::to_string( m_chunkPosition.x ) +
// 				standartSplitChar +
// 				std::to_string( m_chunkPosition.y ) +
// 				standartSplitChar +
// 				std::to_string( m_tilePosition.x ) +
// 				standartSplitChar +
// 				std::to_string( m_tilePosition.y ) +
// 				standartSplitChar +
// 				std::to_string( m_tileID );
			if( m_chunkPosition.size() != m_tilePosition.size() || m_tilePosition.size() != m_tileID.size() )
				REPORT_ERROR_NETWORK( "wrong message parameters" );

			for( int i = 0; i < m_chunkPosition.size(); ++i )
			{
				message += std::to_string( m_chunkPosition.at(i).x );
				message += standartSplitChar;
				message += std::to_string( m_chunkPosition.at( i ).y );
				message += standartSplitChar;
				message += std::to_string( m_tilePosition.at( i ).x );
				message += standartSplitChar;
				message += std::to_string( m_tilePosition.at( i ).y );
				message += standartSplitChar;
				message += std::to_string( m_tileID.at( i ) );
				message += standartSplitChar;
			}

			return message;
		}

		virtual int getID()
		{
			return MESSAGE_ID_CLIENT::SET_TILES_REQUEST;
		}
	};

	class ConnectionRequest : public nMessage
	{
		sf::Uint16 m_recievePortOnClient;
		sf::Uint16 m_recievePortOnServer;

	public:
		//recievePortOnClient: port the client listens to
		//recievePortOnServer: port the server 'should' listens to & sendPort linked to recievePortOnClient by server IP
		ConnectionRequest( sf::Uint16 recievePortOnClient, sf::Uint16 recievePortOnServer )
			:m_recievePortOnClient( recievePortOnClient ),
			m_recievePortOnServer( recievePortOnServer )
		{ }

		virtual std::string getMessage()
		{
			std::string message;
			message += std::to_string( m_recievePortOnClient );
			message += standartSplitChar;
			message += std::to_string( m_recievePortOnServer );

			return message;
		}

		virtual int getID()
		{
			return MESSAGE_ID_CLIENT::CONNECTION_REQUEST;
		}
	};
}
