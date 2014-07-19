//_______Chunk_______//

#pragma once
#include "../stdafx.h"
#include "../Network/Messages.h"
#include "Tile.h"

namespace kg
{
	class Chunk : public DrawableToCamera
	{
		AnimationByIdMap&					 r_tileAnimations;

		const sf::Vector2i                   m_positionInChunks;

		std::map< int, std::map<int, Tile> > m_tiles;


	public:
		//Requests chunkData for this chunks from server on creation
		Chunk( cCore& core, sf::Vector2i positionInChunks, AnimationByIdMap& tileAnimations );

		const Tile&         getTile( sf::Vector2i positionInTiles )const;
		void                setTile( cCore& core, sf::Vector2i relativeTilePosition, const int tileID );

		void                frame( cCore& core );

		virtual void        draw( Camera& camera )override;

		static sf::Vector2i getPositionInPixelForTile( const sf::Vector2i chunkPosition, const sf::Vector2i relativeTilePosition );
	};
}
