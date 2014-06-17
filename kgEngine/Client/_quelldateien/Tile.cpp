#include "../World/Tile.h"

namespace kg
{


	Tile::Tile( cResourceManagement& resourceManagement, int id, sf::Vector2i positionInPixel )
		:m_id(id)
	{
		auto& texture = resourceManagement.getResourceFromResourceFolder<sf::Texture>( "tile" + std::to_string( id )+".png" );

		m_sprite.setTexture( texture );
		//scale the sprite to fit th global Dimensions
		m_sprite.setScale( sf::Vector2f(
			( float )tileSizeInPixel / ( float )texture.getSize().x ,
			( float )tileSizeInPixel / ( float )texture.getSize().y
			));

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

}
