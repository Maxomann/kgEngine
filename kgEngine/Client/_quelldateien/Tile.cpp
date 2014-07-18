#include "../World/Tile.h"

namespace kg
{
	Tile::Tile( cCore& core, int id, sf::Vector2i positionInPixel, AnimationByIdMap& tileAnimations )
		:m_id( id ),
		r_tileAnimations( &tileAnimations )
	{
		core.getExtension<ClientDatabase>()->registerCallback( this,
															   std::bind(
															   &Tile::onTilesModiefied,
															   this,
															   std::placeholders::_1,
															   std::placeholders::_2 ),
															   CALLBACK_ID::CLIENT_DATABASE::TILE_MODIFIED );

		m_loadResources( *core.getExtension<ClientDatabase>() );

		m_sprite.setPosition( sf::Vector2f( positionInPixel ) );
		scaleSpriteToGlobalTileDimensions( m_sprite, r_tileAnimations->at( m_id ) );
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

	void Tile::frame( cCore& core )
	{
		if( m_reload )
		{
			m_loadResources( *core.getExtension<ClientDatabase>() );
			m_reload = false;
		}

		if( !m_errorState )
		{
			auto& animation = r_tileAnimations->at( m_id );
			scaleSpriteToGlobalTileDimensions( m_sprite, animation );
			animation.apply( m_sprite );
		}
	}

	void Tile::onTilesModiefied( int callbackID, ClientDatabase& clientDatabase )
	{
		m_reload = true;
	}

	void Tile::m_loadResources( ClientDatabase& clientDatabase )
	{
		//if tile is not available
		if( !clientDatabase.isTileAvailable( m_id ) )
		{
			r_tileAnimations = nullptr;
			m_errorState = true;
			return;
		}

		auto& tileSettings = clientDatabase.getTile( m_id );

		//ensure that animation for this sprite is loaded
		Animation* animation = nullptr;
		for( auto& el : *r_tileAnimations )
			if( el.first == m_id )
				animation = &(el.second);
		//if not loaded
		if( !animation )
		{
			//load animation from file
			r_tileAnimations->insert( std::make_pair( m_id, Animation( tileSettings ) ) );

			//validate pointer
			for( auto& el : *r_tileAnimations )
				if( el.first == m_id )
					animation = &(el.second);
		}

		auto& texture = clientDatabase.getTileTexture( m_id );

		m_sprite.setTexture( texture );
		animation->apply( m_sprite );

		m_errorState = false;
	}

	void Tile::scaleSpriteToGlobalTileDimensions( sf::Sprite& tile, Animation& tileAnimation )
	{
		tile.setScale( sf::Vector2f(
			( float )tileSizeInPixel / ( float )tileAnimation.getSettings().frameSize.x,
			( float )tileSizeInPixel / ( float )tileAnimation.getSettings().frameSize.x
			) );
	}

}