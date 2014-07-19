//_______Tile_______//

#pragma once
#include "../stdafx.h"
#include "../Drawing/Camera.h"
#include "../Drawing/Animation.h"
#include "../Settings/TileSettings.h"
#include "../ClientDatabase.h"
#include "../ClientDatabaseResourceUser.h"


namespace kg
{
	class Tile : public DrawableToCamera, public aCallbackReciever
	{
		//pointer wegen copy constructor
		AnimationByIdMap*	r_tileAnimations;

		sf::Sprite			m_sprite;

		int					m_id = -1;


		void                m_loadResources( ClientDatabase& clientDatabase );

		bool                m_errorState = false;
		bool                m_reload = false;

	public:
		Tile( cCore& core, int id, sf::Vector2i positionInPixel, AnimationByIdMap& tileAnimations );

		void         onTilesModiefied( int callbackID, ClientDatabase& clientDatabase );
		void         frame( cCore& core );

		int          getID()const;

		virtual void draw( Camera& camera )override;

		static void  scaleSpriteToGlobalTileDimensions( sf::Sprite& tile, Animation& tileAnimation );
	};
}
