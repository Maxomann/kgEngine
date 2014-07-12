//_______BRUSH_SYSTEM_______//

#pragma once
#include "../../stdafx.h"
#include "../../Drawing/Camera.h"

namespace kg
{
	CLIENT_API class Brush : public DrawableToCamera
	{
		bool m_isActive=false;

	protected:
		sf::Vector2i startMousePositionInWorld = { -1, -1 };
		sf::Vector2i startChunkPosition = { -1, -1 };
		sf::Vector2i startRelativeTilePosition = { -1, -1 };

	public:
		virtual ~Brush()
		{ };

		//begins after mouse has been pressed down (not on GUI)
		void begin( sf::Vector2i mousePositionInWorld,
					sf::Vector2i chunkPosition,
					sf::Vector2i relativeTilePosition )
		{
			sf::Vector2i startMousePositionInWorld = mousePositionInWorld;
			sf::Vector2i startChunkPosition = chunkPosition;
			sf::Vector2i startRelativeTilePosition = relativeTilePosition;

			m_isActive = true;
		};

		//not called before begin()
		virtual void cancel()
		{
			m_isActive = false;
		};

		bool isActive()
		{
			return m_isActive;
		};

		//not called before begin()
		virtual void apply( cCore& core,
							sf::Vector2i mousePositionInWorld,
							sf::Vector2i chunkPosition,
							sf::Vector2i relativeTilePosition )
		{
			m_isActive = false;
		};

		virtual void recalculatePreview( cCore& core,
										 sf::Vector2i mousePositionInWorld,
										 sf::Vector2i chunkPosition,
										 sf::Vector2i relativeTilePosition ) = 0;

		//draw preview
		virtual void draw( Camera& camera ) = 0;
	};
}
