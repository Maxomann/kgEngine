//_______WORLD_______//

#pragma once
#include "../stdafx.h"
#include "Chunk.h"

namespace kg
{
	class World
	{
		std::map< std::pair<int, int>, Chunk> m_chunks;

	public:

		Chunk& getChunk( const sf::Vector2i& position );
	};
}