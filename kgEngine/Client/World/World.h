//_______Client_World_______//

#pragma once
#include "../stdafx.h"
#include "Chunk.h"

namespace kg
{
	class World : public DrawableToCamera
	{
		typedef std::map<std::pair<int, int>, Chunk> Chunkmap;
		Chunkmap m_chunks;

		AnimationByIdMap m_tileAnimations;

	public:
		Chunk& getChunk( cCore& core, const sf::Vector2i& positionInChunks );
		void loadChunksInRectAndUnloadOther( cCore& core, const std::vector<sf::IntRect>& rectInPixel );

		void frame( cCore& core );

		virtual void draw( Camera& camera )override;


		static sf::Vector2i getAbsoluteMousePosition( const sf::Window& window, const Camera& camera );

		static sf::Vector2i getAbsoluteChunkPosition( const sf::Window& window, const Camera& camera );

		//relative to absoluteChunkPosition
		static sf::Vector2i getRelativeTilePosition( const sf::Window& window, const Camera& camera );
	};
}
