//_______Chunk_______//

#pragma once
#include "../stdafx.h"
#include "../Camera/Camera.h"
#include "Tile.h"

namespace kg
{
	class Chunk : public DrawableToCamera, public nNetworkConstructable
	{
		const sf::Vector2i m_positionInPixel;

		std::vector<std::vector<Tile>> m_tiles;

	public:
		Chunk( cResourceManagement& resourceManagement, sf::Vector2i positionInPixel );

		const Tile& getTile( sf::Vector2i positionInTiles )const;

		virtual void draw( Camera& camera )override;

		virtual void nFromString( cResourceManagement& resourceManagement, const std::string& data )override;

	};
}
