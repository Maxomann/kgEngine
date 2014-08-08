#include "../Network/Messages.h"

namespace kg
{


	ChunkDataRequest::ChunkDataRequest( const sf::Vector2i& position ) :m_position( position )
	{

	}

	std::string ChunkDataRequest::getMessage()
	{
		return std::to_string( m_position.x ) + standartSplitChar + std::to_string( m_position.y );
	}

	int ChunkDataRequest::getID()
	{
		return MESSAGE_ID_CLIENT::CHUNK_DATA_REQUEST;
	}


	SetTilesRequest::SetTilesRequest( const std::vector< const sf::Vector2i >& chunkPositionInChunks, const std::vector< const sf::Vector2i >& tilePositionRelativeToChunk, const std::vector< const int >& tileID ) :m_chunkPosition( chunkPositionInChunks ),
		m_tilePosition( tilePositionRelativeToChunk ),
		m_tileID( tileID )
	{

	}

	std::string SetTilesRequest::getMessage()
	{
		std::string message;

		if( m_chunkPosition.size() != m_tilePosition.size() || m_tilePosition.size() != m_tileID.size() )
			REPORT_ERROR_NETWORK( "wrong message parameters" );

		for( int i = 0; i < m_chunkPosition.size(); ++i )
		{
			message += std::to_string( m_chunkPosition.at( i ).x );
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

	int SetTilesRequest::getID()
	{
		return MESSAGE_ID_CLIENT::SET_TILES_REQUEST;
	}


	ConnectionRequest::ConnectionRequest( sf::Uint16 recievePortOnClient, sf::Uint16 recievePortOnServer ) : m_recievePortOnClient( recievePortOnClient ),
		m_recievePortOnServer( recievePortOnServer )
	{

	}

	std::string ConnectionRequest::getMessage()
	{
		std::string message;
		message += std::to_string( m_recievePortOnClient );
		message += standartSplitChar;
		message += std::to_string( m_recievePortOnServer );

		return message;
	}

	int ConnectionRequest::getID()
	{
		return MESSAGE_ID_CLIENT::CONNECTION_REQUEST;
	}

}
