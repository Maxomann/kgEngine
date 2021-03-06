#include "../Network/MessageHandlers.h"

namespace kg
{


	void ChunkDataRequestHandler::handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const
	{
		auto seglist = aSplitString::function( std::get<3>( message ), standartSplitChar, aSplitString::operation::REMOVE );
		sf::Vector2i chunkPosition{ atoi( seglist.at( 0 ).c_str() ), atoi( seglist.at( 1 ).c_str() ) };

		core.networkManager.sendMessage(
			std::make_shared<ChunkDataRequestAnswer>( chunkPosition, core.getExtension<Server>()->getWorld().getChunk( chunkPosition ).getFieldData() ),
			std::get<0>( message ),
			core.networkManager.getSendPort( std::get<0>( message ), std::get<1>( message ) )
			);
	}

	int ChunkDataRequestHandler::getMessageHandlerID() const
	{
		return MESSAGE_ID_CLIENT::CHUNK_DATA_REQUEST;
	}

	std::string ChunkDataRequestHandler::info() const
	{
		return __CLASS__;
	}


	void SetTilesRequestHandler::handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const
	{
		auto& world = core.getExtension<Server>()->getWorld();

		std::vector<sf::Vector2i> modifiedChunks;

		auto seglist = aSplitString::function( std::get<3>( message ), standartSplitChar, aSplitString::operation::REMOVE );
		for( int i = 0; i < seglist.size(); ++i )
		{
			sf::Vector2i chunkPosition;
			sf::Vector2i relativeTilePosition;
			int idToSet = 0;

			chunkPosition.x = atoi( seglist.at( i ).c_str() );
			++i;
			chunkPosition.y = atoi( seglist.at( i ).c_str() );
			++i;
			relativeTilePosition.x = atoi( seglist.at( i ).c_str() );
			++i;
			relativeTilePosition.y = atoi( seglist.at( i ).c_str() );
			++i;
			idToSet = atoi( seglist.at( i ).c_str() );
			//++i in for loop

			world.getChunk( chunkPosition ).setField( relativeTilePosition, idToSet );

			//check if chunk has already been modified by this message
			// if not set it on the list to spread to clients
			auto it = std::find( begin( modifiedChunks ), end( modifiedChunks ), chunkPosition );
			if( it == end( modifiedChunks ) )
				modifiedChunks.push_back( chunkPosition );
		}

		//spread new data to clients
		for( const auto& chunkPosition : modifiedChunks )
			core.networkManager.spreadMessage( std::make_shared<ChunkDataRequestAnswer>( chunkPosition, world.getChunk( chunkPosition ).getFieldData() ) );
	}

	int SetTilesRequestHandler::getMessageHandlerID() const
	{
		return MESSAGE_ID_CLIENT::SET_TILES_REQUEST;
	}

	std::string SetTilesRequestHandler::info() const
	{
		return __CLASS__;
	}


	void ConnectionRequestHandler::handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const
	{
		auto seglist = aSplitString::function( std::get<3>( message ), standartSplitChar, aSplitString::operation::REMOVE );
		if( seglist.size() != 2 )
			REPORT_ERROR_NETWORK( "Data transmission failed" );

		core.networkManager.addConnection( std::get<0>( message ),
										   atoi( seglist.at( 1 ).c_str() ),//recievePort : recievePortOnServer
										   atoi( seglist.at( 0 ).c_str() ) );//sendPort : recievePortOnClient

		core.networkManager.sendMessage( std::make_shared<ConnectionRequestAnswer>( atoi( seglist.at( 1 ).c_str() ), true ),
										 std::get<0>( message ),//IP
										 atoi( seglist.at( 0 ).c_str() ) );//recievePortOnClient
	}

	int ConnectionRequestHandler::getMessageHandlerID() const
	{
		return MESSAGE_ID_CLIENT::CONNECTION_REQUEST;
	}

	std::string ConnectionRequestHandler::info() const
	{
		return __CLASS__;
	}

}
