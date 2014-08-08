//_______Tile_______//

#pragma once
#include "../stdafx.h"
#include "../Drawing/Camera.h"
#include "../Drawing/Animation.h"
#include "../Settings/TileSettings.h"
#include "../ClientDatabase.h"


namespace kg
{
	class Tile : public DrawableToCamera, public aCallbackReciever, public sf::NonCopyable
	{
		sf::Sprite			m_sprite;

		int					m_id = -1;


		void                m_initResources( ClientDatabase& clientDatabase, AnimationByIdMap& tileAnimations );

		bool                m_errorState = false;
		bool                m_reload = false;

		void				m_onTilesModified( const int& callbackID, const ClientDatabase& clientDatabase );

	public:
		Tile( cCore& core, int id, sf::Vector2i positionInPixel, AnimationByIdMap& tileAnimations );

		void		 frame( cCore& core, AnimationByIdMap& tileAnimations );

		int          getID()const;

		virtual void draw( Camera& camera )override;

		static void  scaleSpriteToGlobalTileDimensions( sf::Sprite& tile, Animation& tileAnimation );
	};
}
