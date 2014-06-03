//_______FIELD_H_______//
#pragma once
#include"stdafx.h"
#include"cCamera.h"

namespace kg
{
	//For pointer
	class cFieldFactory;

	FACTORY class cField : public cFocusable
	{
	private:
		cFieldFactory*		r_factory;

		const sf::Vector2i	m_positionInTiles;
		sf::Sprite			m_sprite;

	public:
		cField( sf::Texture& texture,
				const sf::Vector2i& positionOnTexture,
				int textureSizeInPixel,
				int finalSizeInPixel,
				const sf::Vector2i& positionInTiles,
				cFieldFactory* factory );

		const cFieldFactory*	getFactory()const;

		const sf::Vector2i	getPositionInTiles()const;

		void				update();

		void				draw( cCamera& camera );
	};
}
