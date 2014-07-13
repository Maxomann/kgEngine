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
					Chunk::getPositionInPixelForTile( m_positionInChunks, sf::Vector2i(x,y) ),
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

	sf::Vector2i Chunk::getPositionInPixelForTile( const sf::Vector2i chunkPosition, const sf::Vector2i relativeTilePosition )
	{
		return chunkSizeInTiles*tileSizeInPixel*chunkPosition + tileSizeInPixel*relativeTilePosition;
	}

	void Chunk::setTile( cCore& core, sf::Vector2i relativeTilePosition, const int tileID )
	{
		auto& tile = m_tiles.at( relativeTilePosition.x ).at( relativeTilePosition.y );
		if( tileID != tile.getID() )
			tile = Tile(
			core,
			tileID,
			Chunk::getPositionInPixelForTile(m_positionInChunks,relativeTilePosition),
			r_tileAnimations );
	}
}
