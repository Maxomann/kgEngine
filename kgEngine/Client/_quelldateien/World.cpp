#include "../World/World.h"

namespace kg
{
	Chunk& World::getChunk( cResourceManagement& resourceManagement, const sf::Vector2i& positionInChunks )
	{
		for( auto& el : m_chunks )
		{
			if( el.first == std::make_pair( positionInChunks.x, positionInChunks.y ) )
			{
				return el.second;
			}
		}

		//Chunk needs to be constructed
		m_chunks.emplace( std::make_pair( std::make_pair( positionInChunks.x, positionInChunks.y ),
			Chunk( resourceManagement,
			sf::Vector2i( positionInChunks.x*chunkSizeInTiles*tileSizeInPixel,
			positionInChunks.y*chunkSizeInTiles*tileSizeInPixel
			)
			) ) );
		return m_chunks.at( std::make_pair( positionInChunks.x, positionInChunks.y ) );
	}

	void World::draw( Camera& camera )
	{
		for( auto& el : m_chunks )
			el.second.draw( camera );
	}

}
