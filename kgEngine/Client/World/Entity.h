//_______ENTITY_______//

#pragma once
#include "../stdafx.h"
#include "../Drawing/Camera.h"
#include "../Drawing/Animation.h"

namespace kg
{
	class Entity : public DrawableToCamera, public aCallbackReciever, public sf::NonCopyable
	{
	public:
		Entity( cCore& core,
				const int entityID,
				const sf::Vector2i positionInPixel );

		void setPosition( const sf::Vector2i positionInPixel );
		const sf::Vector2i getPosition()const;

		void frame( cCore& core );

		virtual void draw( Camera& camera );
	
	};
}
