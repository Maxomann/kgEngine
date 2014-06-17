//_______Tile_______//

#pragma once
#include "../stdafx.h"
#include "../Camera/Camera.h"

namespace kg
{
	class Tile : public DrawableToCamera
	{
		sf::Sprite m_sprite;

		int m_id = -1;

	public:
		Tile( cResourceManagement& resourceManagement, int id, sf::Vector2i positionInPixel );

		int getID()const;

		virtual void draw( Camera& camera )override;
	};

}
