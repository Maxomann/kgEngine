//_______Client_World_______//

#pragma once
#include "../stdafx.h"
#include "../Camera/Camera.h"
#include "Chunk.h"

namespace kg
{
	class World : public DrawableToCamera
	{
		std::map<std::pair<int, int>, Chunk> m_chunks;

	public:
		Chunk& getChunk( cCore& core, const sf::Vector2i& positionInChunks );

		void frame( cCore& core );

		virtual void draw( Camera& camera )override;
	};
}
