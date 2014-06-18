//_______Chunk_______//

#pragma once
#include "../stdafx.h"
#include "../Camera/Camera.h"
#include "Tile.h"

namespace kg
{
	class Chunk : public DrawableToCamera, public nNetworkConstructable
	{
		const sf::Vector2i m_positionInChunks;

		std::vector<std::vector<Tile>> m_tiles;

	public:
		Chunk( cCore& core, sf::Vector2i positionInChunks );

		const Tile& getTile( sf::Vector2i positionInTiles )const;

		virtual void draw( Camera& camera )override;

		virtual void nFromString( cCore& core, const std::string& data )override;
	};
}
