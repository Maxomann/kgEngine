//_______BRUSH_SYSTEM_______//

#pragma once
#include "../../stdafx.h"
#include "../../Drawing/Camera.h"

namespace kg
{
	CLIENT_API class Brush : public DrawableToCamera
	{
	public:
		virtual ~Brush()
		{ };

		//begins after mouse has been pressed down (not on GUI)
		virtual void begin()=0;

		//not called before begin()
		virtual void apply()=0;
		//not called before begin()
		virtual void cancel()=0;

		virtual void recalculatePreview( sf::Vector2i chunkPosition, sf::Vector2i relativeTilePosition ) = 0;

		//draw preview
		virtual void draw( Camera& camera )=0;

	};
}
