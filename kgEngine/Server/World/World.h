//_______WORLD_______//

#pragma once
#include "../stdafx.h"
#include "Chunk.h"

namespace kg
{
	class World
	{
		std::map<sf::Vector2i, Chunk> m_chunks;

	public:

		Chunk& getChunk( const sf::Vector2i& position );

	};
}