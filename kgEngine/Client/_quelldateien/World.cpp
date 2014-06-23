#include "../World/World.h"

namespace kg
{
	Chunk& World::getChunk( cCore& core, const sf::Vector2i& positionInChunks )
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
			Chunk( core,
			sf::Vector2i( positionInChunks.x, positionInChunks.y ),
			m_tileAnimations
			) ) );
		return m_chunks.at( std::make_pair( positionInChunks.x, positionInChunks.y ) );
	}

	void World::draw( Camera& camera )
	{
		for( auto& el : m_chunks )
			el.second.draw( camera );
	}

	void World::frame( cCore& core )
	{
		for( auto& chunk : m_chunks )
			chunk.second.frame( core );
		for( auto& animation : m_tileAnimations )
			animation.second.frame();
	}

	void World::loadChunksInRectAndUnloadOther( cCore& core, const std::vector<sf::IntRect>& rectsInPixelVector )
	{
		std::vector<sf::Vector2i> positions;

		for( const auto& rectInPixel : rectsInPixelVector )
		{
			int top = rectInPixel.top / (chunkSizeInTiles*tileSizeInPixel);
			int left = rectInPixel.left / (chunkSizeInTiles*tileSizeInPixel);
			int right = (rectInPixel.left + rectInPixel.width) / (chunkSizeInTiles*tileSizeInPixel);
			int bottom = (rectInPixel.top + rectInPixel.height) / (chunkSizeInTiles*tileSizeInPixel);

			top -= 1;
			left -= 1;
			right += 1;
			bottom += 1;

			for( int x = left; x <= right; ++x )
			{
				for( int y = top; y <= bottom; ++y )
				{
					positions.push_back( sf::Vector2i( x, y ) );
					getChunk( core, sf::Vector2i( x, y ) );
				}
			}
		}

		std::vector<Chunkmap::iterator> chunksNotInRect;
		for( Chunkmap::iterator it = m_chunks.begin(); it != m_chunks.end(); ++it )
		{
			if( !std::any_of( positions.begin(), positions.end(), [&]( sf::Vector2i& el )
			{
				return sf::Vector2i( it->first.first, it->first.second ) == el;
			} ) )
			{
				chunksNotInRect.push_back( it );
			}
		}

		for( const auto& el : chunksNotInRect )
			m_chunks.erase( el );
	}

}
