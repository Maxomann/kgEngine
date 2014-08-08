#include "../GameState/Editor/BrushSystem.h"

namespace kg
{


	void Brush::begin( sf::Vector2i mousePositionInWorld, sf::Vector2i chunkPosition, sf::Vector2i relativeTilePosition )
	{
		sf::Vector2i startMousePositionInWorld = mousePositionInWorld;
		sf::Vector2i startChunkPosition = chunkPosition;
		sf::Vector2i startRelativeTilePosition = relativeTilePosition;

		m_isActive = true;
	}

	void Brush::cancel()
	{
		m_isActive = false;
	}

	bool Brush::isActive()
	{
		return m_isActive;
	}

	void Brush::apply( cCore& core, sf::Vector2i mousePositionInWorld, sf::Vector2i chunkPosition, sf::Vector2i relativeTilePosition )
	{
		m_isActive = false;
	}

}
