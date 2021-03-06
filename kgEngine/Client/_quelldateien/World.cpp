#include "../World/World.h"

namespace kg
{
	Chunk* World::getChunk( cCore& core, const sf::Vector2i& positionInChunks )
	{
		for( auto& el : m_chunks )
		{
			if( el.first == std::make_pair( positionInChunks.x, positionInChunks.y ) )
			{
				return el.second.get();
			}
		}

		return nullptr;
	}

	void World::draw( Camera& camera )
	{
		for( auto& el : m_chunks )
			el.second->draw( camera );
	}

	void World::frame( cCore& core )
	{
		for( auto& chunk : m_chunks )
			chunk.second->frame( core, m_tileAnimations );
		for( auto& animation : m_tileAnimations )
			animation.second.frame();
	}

	void World::loadChunksInRectAndUnloadOther( cCore& core, const std::vector<sf::IntRect>& rectsInPixelVector )
	{
		std::vector<sf::Vector2i> positionsInRect;

		for( const auto& rectInPixel : rectsInPixelVector )
		{
			int top = rectInPixel.top / (chunkSizeInTiles*tileSizeInPixel);
			int left = rectInPixel.left / (chunkSizeInTiles*tileSizeInPixel);
			int right = (rectInPixel.left + rectInPixel.width) / (chunkSizeInTiles*tileSizeInPixel);
			int bottom = (rectInPixel.top + rectInPixel.height) / (chunkSizeInTiles*tileSizeInPixel);

			top -= 1;
			left -= 1;
			right += 1;
			bottom += 1;

			for( int x = left; x <= right; ++x )
			{
				for( int y = top; y <= bottom; ++y )
				{
					positionsInRect.push_back( sf::Vector2i( x, y ) );
					loadChunk( core, sf::Vector2i( x, y ) );
				}
			}
		}

		std::vector<Chunkmap::iterator> chunksNotInRect;
		for( Chunkmap::iterator it = m_chunks.begin(); it != m_chunks.end(); ++it )
		{
			if( !std::any_of( positionsInRect.begin(), positionsInRect.end(), [&]( sf::Vector2i& el )
			{
				return sf::Vector2i( it->first.first, it->first.second ) == el;
			} ) )
			{
				chunksNotInRect.push_back( it );
			}
		}

		for( const auto& el : chunksNotInRect )
			m_chunks.erase( el );
	}

	sf::Vector2i World::getAbsoluteMousePosition( const sf::RenderWindow& window, const Camera& camera )
	{
		sf::Vector2i mousePosition( sf::Mouse::getPosition( window ) );
		sf::Vector2i transformedMousePosition( window.mapPixelToCoords( mousePosition, camera.getView() ) );

		return transformedMousePosition;
	}

	sf::Vector2i World::getAbsoluteChunkPosition( const sf::RenderWindow& window, const Camera& camera )
	{
		sf::Vector2i positionInWorld( getAbsoluteMousePosition( window, camera ) );

		sf::Vector2i chunkPosition( positionInWorld / (chunkSizeInTiles*tileSizeInPixel) );
		if( positionInWorld.x < 1 )
			chunkPosition.x -= 1;
		if( positionInWorld.y < 1 )
			chunkPosition.y -= 1;

		return chunkPosition;
	}

	sf::Vector2i World::getRelativeTilePosition( const sf::RenderWindow& window, const Camera& camera )
	{
		sf::Vector2i positionInWorld( getAbsoluteMousePosition( window, camera ) );
		auto chunkPosition = getAbsoluteChunkPosition( window, camera );

		sf::Vector2i tilePosition( (positionInWorld / tileSizeInPixel) - (chunkPosition*chunkSizeInTiles) );
		if( positionInWorld.x < 1 )
			tilePosition.x -= 1;
		if( positionInWorld.y < 1 )
			tilePosition.y -= 1;

		return tilePosition;
	}

	void World::reset()
	{
		m_chunks.clear();
		m_tileAnimations.clear();
	}

	void World::onInit( cCore& core )
	{
		core.getExtension<ClientDatabase>()->registerCallback( this,
															   std::bind(
															   &World::m_onTilesModified,
															   this,
															   std::placeholders::_1,
															   std::placeholders::_2 ),
															   CALLBACK_ID::CLIENT_DATABASE::TILE_MODIFIED );
	}

	void World::m_onTilesModified( const int& callbackID, const ClientDatabase& clientDatabase )
{
		m_tileAnimations.clear();
	}

	Chunk& World::loadChunk( cCore& core, const sf::Vector2i& positionInChunks )
	{
		for( auto& el : m_chunks )
		{
			if( el.first == std::make_pair( positionInChunks.x, positionInChunks.y ) )
			{
				return *el.second.get();
			}
		}

		//Chunk needs to be constructed
		m_chunks.emplace(
			std::make_pair( positionInChunks.x, positionInChunks.y ),
			std::make_unique<Chunk>( core,
			sf::Vector2i( positionInChunks.x, positionInChunks.y ),
			m_tileAnimations
			) );
		return *m_chunks.at( std::make_pair( positionInChunks.x, positionInChunks.y ) ).get();
	}

	// 	sf::IntRect World::getAbsoluteWindowRect( const sf::RenderWindow& window, const Camera& camera )
	// 	{
	// 		auto cameraRect = camera.getCameraRectWithoutRotation();
	// 		auto leftTop = rotatePointAroundPoint<float>(
	// 			sf::Vector2f( cameraRect.left, cameraRect.top ),
	// 			-camera.getRotation(),
	// 			sf::Vector2f( cameraRect.left + cameraRect.width / 2, cameraRect.top + cameraRect.height / 2 ) );
	//
	// 	}

	// 				sf::Vector2i mousePosition( sf::Mouse::getPosition( *gui.getWindow() ) );
	// 				mousePosition.x /= camera.getZoom();
	// 				mousePosition.y /= camera.getZoom();
	// 				sf::Vector2i cameraOffset= camera.getUpperLeftCorner();
	// 				sf::Vector2i positionInWorld( mousePosition + cameraOffset );
	//
	// 				sf::Vector2i chunkPosition( positionInWorld / (chunkSizeInTiles*tileSizeInPixel) );
	// 				if( positionInWorld.x < 1 )
	// 					chunkPosition.x -= 1;
	// 				if( positionInWorld.y < 1 )
	// 					chunkPosition.y -= 1;
	//
	// 				sf::Vector2i tilePosition( (positionInWorld / tileSizeInPixel) - (chunkPosition*chunkSizeInTiles) );
	// 				if( positionInWorld.x < 1 )
	// 					tilePosition.x -= 1;
	// 				if( positionInWorld.y < 1 )
	// 					tilePosition.y -= 1;
}