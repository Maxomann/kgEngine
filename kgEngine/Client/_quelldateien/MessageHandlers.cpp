#include "../Network/MessageHandlers.h"

namespace kg
{


	void ChunkDataRequestAnswerHandler::handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const
	{
		auto& data = std::get<3>( message );

		std::string chunkX;
		std::string chunkY;

		while( data.at( 0 ) != standartSplitChar )
		{
			chunkX.push_back( data.at( 0 ) );
			data.erase( data.begin() );
		}
		data.erase( data.begin() );
		while( data.at( 0 ) != standartSplitChar )
		{
			chunkY.push_back( data.at( 0 ) );
			data.erase( data.begin() );
		}
		data.erase( data.begin() );

		auto chunk = core.getExtension<Client>()->getWorld().getChunk( core, sf::Vector2i( atoi( chunkX.c_str() ), atoi( chunkY.c_str() ) ) );
		if( !chunk )
			return;

		auto seglist = aSplitString::function( data, standartSplitChar, aSplitString::operation::REMOVE );
		for( int x = 0; x < chunkSizeInTiles; ++x )
		{
			for( int y = 0; y < chunkSizeInTiles; ++y )
			{
				int id = atoi( seglist.at( x*chunkSizeInTiles + y ).c_str() );
				chunk->setTile( core, sf::Vector2i( x, y ), id );
			}
		}
	}

	int ChunkDataRequestAnswerHandler::getMessageHandlerID() const
	{
		return MESSAGE_ID_SERVER::CHUNK_DATA_REQUEST_ANSWER;
	}

	std::string ChunkDataRequestAnswerHandler::info() const
	{
		return __CLASS__;
	}


	void ConnectionRequestAnswerHandler::handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const
	{
		auto seglist = aSplitString::function( std::get<3>( message ), standartSplitChar, aSplitString::operation::REMOVE );
		if( seglist.size() != 2 )
			REPORT_ERROR_NETWORK( "Data transmission failed" );

		bool accepted = atoi( seglist.at( 0 ).c_str() );
		if( !accepted )
			REPORT_ERROR_NETWORK( "connection refused" );
		core.setServerIp( std::get<0>( message ) );
		core.setServerPort( atoi( seglist.at( 1 ).c_str() ) );

		core.getExtension<Client>()->getWorld().reset();
	}

	int ConnectionRequestAnswerHandler::getMessageHandlerID() const
	{
		return MESSAGE_ID_SERVER::CONNECTION_REQUEST_ANSWER;
	}

	std::string ConnectionRequestAnswerHandler::info() const
	{
		return __CLASS__;
	}

}
