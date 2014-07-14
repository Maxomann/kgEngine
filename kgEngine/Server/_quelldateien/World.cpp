#include "../World/World.h"

namespace kg
{
	Chunk& World::getChunk( const sf::Vector2i& position )
	{
		return m_chunks[std::make_pair( position.x, position.y )];
	}
}