//_______Client_World_______//

#pragma once
#include "../stdafx.h"
#include "Chunk.h"

namespace kg
{
	class World : public DrawableToCamera, public aCallbackReciever, public sf::NonCopyable
	{
		typedef std::map<std::pair<int, int>, Chunk> Chunkmap;
		Chunkmap         m_chunks;

		AnimationByIdMap m_tileAnimations;

		void m_onTilesModified( int& callbackID, ClientDatabase& clientDatabase );

	public:
		void onInit( cCore& core );

		Chunk&              getChunk( cCore& core, const sf::Vector2i& positionInChunks );
		void                loadChunksInRectAndUnloadOther( cCore& core, const std::vector<sf::IntRect>& rectInPixel );

		//resets the world, so information has to be reloaded from server and ClientDatabase
		void                reset();

		void                frame( cCore& core );

		virtual void        draw( Camera& camera )override;

		static sf::Vector2i getAbsoluteMousePosition( const sf::RenderWindow& window, const Camera& camera );

		//in chunks
		static sf::Vector2i getAbsoluteChunkPosition( const sf::RenderWindow& window, const Camera& camera );

		//relative to       absoluteChunkPosition (in tiles)
		static sf::Vector2i getRelativeTilePosition( const sf::RenderWindow& window, const Camera& camera );
	};
}
