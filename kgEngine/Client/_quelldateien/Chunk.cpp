#include "../World/Chunk.h"

namespace kg
{

	Chunk::Chunk( cCore& core, sf::Vector2i positionInChunks, AnimationByIdMap& tileAnimations )
		:m_positionInChunks( positionInChunks ),
		r_tileAnimations( tileAnimations )
	{
		//standart initialize fields
		for( int x = 0; x < chunkSizeInTiles; ++x )
		{
			m_tiles.push_back( std::vector<Tile>() );
			for( int y = 0; y < chunkSizeInTiles; ++y )
			{
				m_tiles.at( x ).push_back(
					Tile(
					core,
					0,
					sf::Vector2i( m_positionInChunks.x*chunkSizeInTiles*tileSizeInPixel + x*tileSizeInPixel, m_positionInChunks.y*chunkSizeInTiles*tileSizeInPixel + y*tileSizeInPixel ),
					tileAnimations )
					);
			}
		}

		//request chunkData from server
		core.networkManager.sendMessage( std::make_shared<ChunkDataRequest>( m_positionInChunks ), core.getServerIp(), core.getServerPort() );
	}

	void Chunk::draw( Camera& camera )
	{
		for( auto& el : m_tiles )
			for( auto& tile : el )
				tile.draw( camera );
	}

	void Chunk::nFromString( cCore& core, const std::string& data )
	{
		auto seglist = aSplitString::function( data, standartSplitChar, aSplitString::operation::REMOVE );

		for( int x = 0; x < chunkSizeInTiles; ++x )
		{
			for( int y = 0; y < chunkSizeInTiles; ++y )
			{
				auto& tile = m_tiles.at( x ).at( y );
				int id = atoi( seglist.at( x*chunkSizeInTiles + y ).c_str() );
				if( id != tile.getID() )
					tile = Tile(
					core,
					id,
					sf::Vector2i(
					m_positionInChunks.x*chunkSizeInTiles*tileSizeInPixel + x*tileSizeInPixel,
					m_positionInChunks.y*chunkSizeInTiles*tileSizeInPixel + y*tileSizeInPixel
					),
					r_tileAnimations );
			}
		}
	}

	const Tile& Chunk::getTile( sf::Vector2i positionInTiles ) const
	{
		return m_tiles.at( positionInTiles.x ).at( positionInTiles.y );
	}

	void Chunk::frame( cCore& core )
	{
		for( auto& x : m_tiles )
			for( auto& y : x )
				y.frame( core );
	}

}
