//_______Chunk_______//

#pragma once
#include "../stdafx.h"
#include "../Network/Messages.h"
#include "Tile.h"

namespace kg
{
	class Chunk : public DrawableToCamera, public sf::NonCopyable
	{
		AnimationByIdMap&					 r_tileAnimations;

		const sf::Vector2i                   m_positionInChunks;

		std::array< std::array< std::unique_ptr<Tile>, chunkSizeInTiles >, chunkSizeInTiles > m_tiles;


	public:
		//Requests chunkData for this chunks from server on creation
		Chunk( cCore& core, sf::Vector2i positionInChunks, AnimationByIdMap& tileAnimations );

		//can be nullptr if tile has not been loaded
		const Tile*         getTile( sf::Vector2i positionInTiles )const;
		//will not change the tile if tile.getID() == tileID
		void                setTile( cCore& core, sf::Vector2i relativeTilePosition, const int tileID );

		void				frame( cCore& core, AnimationByIdMap& tileAnimations );

		virtual void        draw( Camera& camera )override;

		static sf::Vector2i getPositionInPixelForTile( const sf::Vector2i chunkPosition, const sf::Vector2i relativeTilePosition );
	};
}
