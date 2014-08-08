#include "../Network/Messages.h"

namespace kg
{


	ChunkDataRequestAnswer::ChunkDataRequestAnswer( const sf::Vector2i& position, const std::array< std::array<int, chunkSizeInTiles>, chunkSizeInTiles >& chunkData )
	{
		m_message += std::to_string( position.x );
		m_message += standartSplitChar;
		m_message += std::to_string( position.y );
		m_message += standartSplitChar;

		for( int x = 0; x < chunkSizeInTiles; ++x )
		{
			for( int y = 0; y < chunkSizeInTiles; ++y )
			{
				m_message += std::to_string( chunkData[x][y] );
				m_message.push_back( standartSplitChar );
			}
		}
	}

	std::string ChunkDataRequestAnswer::getMessage()
	{
		return m_message;
	}

	int ChunkDataRequestAnswer::getID()
	{
		return MESSAGE_ID_SERVER::CHUNK_DATA_REQUEST_ANSWER;
	}


	ConnectionRequestAnswer::ConnectionRequestAnswer( sf::Uint16 recievePortOnServer, bool accepted /*= true */ ) : m_accepted( accepted ),
		m_recievePortOnServer( recievePortOnServer )
	{

	}

	std::string ConnectionRequestAnswer::getMessage()
	{
		std::string message( std::to_string( m_accepted ) );
		message += standartSplitChar;
		message += std::to_string( m_recievePortOnServer );

		return message;
	}

	int ConnectionRequestAnswer::getID()
	{
		return MESSAGE_ID_SERVER::CONNECTION_REQUEST_ANSWER;
	}

}
