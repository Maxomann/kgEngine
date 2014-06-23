//_______Chunk_______//

#pragma once
#include "../stdafx.h"
#include "../Network/Messages.h"
#include "Tile.h"

namespace kg
{
	class Chunk : public DrawableToCamera, public nNetworkConstructable
	{
		AnimationByIdMap& r_tileAnimations;


		const sf::Vector2i m_positionInChunks;

		std::vector<std::vector<Tile>> m_tiles;

	public:
		//Requests chunkData for this chunks from server on creation
		Chunk( cCore& core, sf::Vector2i positionInChunks, AnimationByIdMap& tileAnimations );

		const Tile& getTile( sf::Vector2i positionInTiles )const;

		void frame( cCore& core );

		virtual void draw( Camera& camera )override;

		virtual void nFromString( cCore& core, const std::string& data )override;
	};
}
