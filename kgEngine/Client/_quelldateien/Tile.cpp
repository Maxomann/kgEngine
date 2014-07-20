#include "../World/Tile.h"

namespace kg
{
	static std::vector<Tile*> debugVector;

	Tile::Tile( cCore& core, int id, sf::Vector2i positionInPixel, AnimationByIdMap& tileAnimations )
		:m_id( id )
	{
		core.getExtension<ClientDatabase>()->registerCallback( this,
															   std::bind(
															   &Tile::m_onTilesModified,
															   this,
															   std::placeholders::_1,
															   std::placeholders::_2 ),
															   CALLBACK_ID::CLIENT_DATABASE::TILE_MODIFIED );

		m_initResources( *core.getExtension<ClientDatabase>(), tileAnimations );

		m_sprite.setPosition( sf::Vector2f( positionInPixel ) );
		scaleSpriteToGlobalTileDimensions( m_sprite, tileAnimations.at( m_id ) );
	}

	void Tile::draw( Camera& camera )
	{
		if( !m_errorState )
			camera.draw( m_sprite, Camera::TILE );
	}

	int Tile::getID() const
	{
		return m_id;
	}

	void Tile::frame( cCore& core, AnimationByIdMap& tileAnimations )
	{
		if( m_reload )
			m_initResources( *core.getExtension<ClientDatabase>(), tileAnimations );

		if( !m_errorState )
		{
			auto& animation = tileAnimations.at( m_id );
			scaleSpriteToGlobalTileDimensions( m_sprite, animation );
			animation.apply( m_sprite );
		}
	}

	void Tile::m_onTilesModified( const int& callbackID, const ClientDatabase& clientDatabase )
	{
		m_reload = true;
	}

	void Tile::m_initResources( ClientDatabase& clientDatabase, AnimationByIdMap& tileAnimations )
	{
		//if tile is not available
		if( !clientDatabase.isTileAvailable( m_id ) )
		{
			m_errorState = true;
			return;
		}

		auto& tileSettings = clientDatabase.getTile( m_id );

		//ensure that animation for this sprite is loaded
		Animation* animation = nullptr;
		for( auto& el : tileAnimations )
			if( el.first == m_id )
				animation = &(el.second);
		//if not loaded
		if( !animation )
		{
			//load animation from file
			tileAnimations.emplace( m_id, tileSettings );

			//validate pointer
			for( auto& el : tileAnimations )
				if( el.first == m_id )
					animation = &(el.second);
		}

		auto& texture = clientDatabase.getTileTexture( m_id );

		m_sprite.setTexture( texture );
		animation->apply( m_sprite );

		m_errorState = false;
		m_reload = false;
	}

	void Tile::scaleSpriteToGlobalTileDimensions( sf::Sprite& tile, Animation& tileAnimation )
	{
		tile.setScale( sf::Vector2f(
			( float )tileSizeInPixel / ( float )tileAnimation.getSettings().frameSize.x,
			( float )tileSizeInPixel / ( float )tileAnimation.getSettings().frameSize.x
			) );
	}

}