#pragma once
#include "../stdafx.h"

namespace kg
{
	class ChunkDataRequestAnswer : public nMessage
	{
		std::string m_message;

	public:
		ChunkDataRequestAnswer( const sf::Vector2i& position, const Chunk& chunk )
		{
			m_message += std::to_string( position.x );
			m_message += standartSplitChar;
			m_message += std::to_string( position.y );
			m_message += standartSplitChar;

			for( int x = 0; x < chunkSizeInTiles; ++x )
			{
				for( int y = 0; y < chunkSizeInTiles; ++y )
				{
					m_message += std::to_string( chunk.getField(sf::Vector2i(x,y)) );
					m_message.push_back( standartSplitChar );
				}
			}
		}

		virtual std::string getMessage()
		{
			return m_message;
		}

		virtual int getID()
		{
			return MESSAGE_ID_SERVER::CHUNK_DATA_REQUEST_ANSWER;
		}
	};

	class ConnectionRequestAnswer : public nMessage
	{
		bool m_accepted = false;
		sf::Uint16 m_recievePortOnServer;

	public:
		ConnectionRequestAnswer( sf::Uint16 recievePortOnServer, bool accepted = true )
			: m_accepted( accepted ),
			m_recievePortOnServer( recievePortOnServer )
		{
		}

		virtual std::string getMessage()
		{
			std::string message( std::to_string( m_accepted ) );
			message += standartSplitChar;
			message += std::to_string( m_recievePortOnServer );

			return message;
		}

		virtual int getID()
		{
			return MESSAGE_ID_SERVER::CONNECTION_REQUEST_ANSWER;
		}
	};
}
