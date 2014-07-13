#include "../World/Tile.h"

namespace kg
{
	Tile::Tile( cCore& core, int id, sf::Vector2i positionInPixel, AnimationByIdMap& tileAnimations )
		:m_id( id ),
		r_tileAnimations( &tileAnimations )
	{
		auto& tileSettings = core.getExtension<ClientDatabase>()->getTile( id );

		//ensure that animation for this sprite is loaded
		Animation* animation = nullptr;
		for( auto& el : tileAnimations )
			if( el.first == m_id )
				animation = &(el.second);
		//if not loaded
		if( !animation )
		{
			//load animation from file
			tileAnimations.insert( std::make_pair( m_id, Animation( tileSettings ) ) );

			//validate pointer
			for( auto& el : tileAnimations )
				if( el.first == m_id )
					animation = &(el.second);
		}

		auto& texture = core.getExtension<ClientDatabase>()->getTileTexture( id );

		m_sprite.setTexture( texture );
		animation->apply( m_sprite );

		m_sprite.setPosition( sf::Vector2f( positionInPixel ) );
	}

	void Tile::draw( Camera& camera )
	{
		camera.draw( m_sprite, Camera::TILE );
	}

	int Tile::getID() const
	{
		return m_id;
	}

	void Tile::frame( cCore& core )
	{
		r_tileAnimations->at( m_id ).apply( m_sprite );
	}
}