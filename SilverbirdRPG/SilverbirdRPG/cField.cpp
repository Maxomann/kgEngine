//_______FIELD_CPP_______//
#pragma once
#include "cField.h"

namespace kg
{
#pragma message("warning: TODO: FieldAnimation")
	cField::cField( sf::Texture& texture,
					const sf::Vector2i& positionOnTexture,
					int textureSizeInPixel,
					int finalSizeInPixel,
					const sf::Vector2i& positionInTiles,
					cFieldFactory* factory )
					: m_positionInTiles( positionInTiles ),
					r_factory( factory )
	{
		m_sprite.setTexture( texture );
		m_sprite.setTextureRect( sf::IntRect( positionOnTexture.x,
			positionOnTexture.y,
			textureSizeInPixel,
			textureSizeInPixel ) );

		m_sprite.setPosition( sf::Vector2f( static_cast< float >(finalSizeInPixel*positionInTiles.x), static_cast< float >(finalSizeInPixel * positionInTiles.y) ) );
		m_sprite.setScale( sf::Vector2f( static_cast< float >(finalSizeInPixel) / static_cast< float >(textureSizeInPixel), static_cast< float >(finalSizeInPixel) / static_cast< float >(textureSizeInPixel) ) );
	}
	const cFieldFactory* cField::getFactory()const
	{
		return r_factory;
	}
	const sf::Vector2i cField::getPositionInTiles()const
	{
		return m_positionInTiles;
	}
	void cField::update()
	{
		//Update Animation here
	}
	void cField::draw( cCamera& camera )
	{
		//Do not draw if field is not seen on Camera
		if( this->m_sprite.getGlobalBounds().intersects( camera.getCameraRect() ) )
			camera.draw( m_sprite, cCamera::TILE );
	}
}