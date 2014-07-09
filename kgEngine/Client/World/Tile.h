//_______Tile_______//

#pragma once
#include "../stdafx.h"
#include "../Drawing/Camera.h"
#include "../Drawing/Animation.h"
#include "../Settings/TileSettings.h"
#include "../ClientDatabase.h"

namespace kg
{
	class Tile : public DrawableToCamera
	{
		//pointer wegen copy constructor
		AnimationByIdMap* r_tileAnimations;

		sf::Sprite m_sprite;

		int m_id = -1;

	public:
		Tile( cCore& core, int id, sf::Vector2i positionInPixel, AnimationByIdMap& tileAnimations );

		void frame( cCore& core );

		int getID()const;

		virtual void draw( Camera& camera )override;
	};
}
