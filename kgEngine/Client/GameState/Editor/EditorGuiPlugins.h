//_______GUI_PLUGINS_______//

#pragma once
#include "EditorGuiElements.h"
#include "../../World/Chunk.h"

namespace kg
{
	class PointBrush : public Brush
	{
		//pair.first = chunkPosition; pair.second = relativeTilePosition
		std::vector< std::pair<sf::Vector2i, sf::Vector2i> > m_tilePositionsToSet;

		std::vector< sf::Sprite > m_previewTiles;

		int m_tileId;

	public:
		PointBrush( int selectedTileId );

		virtual void apply( cCore& core,
							sf::Vector2i mousePositionInWorld,
							sf::Vector2i chunkPosition,
							sf::Vector2i relativeTilePosition );

		virtual void recalculatePreview( cCore& core,
										 sf::Vector2i mousePositionInWorld,
										 sf::Vector2i chunkPosition,
										 sf::Vector2i relativeTilePosition );

		virtual void draw( Camera& camera );

		virtual void cancel();

	};

	class PointBrushSubWindow : public TileDrawingSubWindow
	{
		tgui::ListBox::Ptr m_tileSelectionBox;

		void m_refreshTileSelectonBox( cCore& core );

		void m_callback( const tgui::Callback& callback );

		bool m_hasBrushChanged = true;

	public:
		virtual void onInit( cCore& core, tgui::Container& container );

		virtual std::unique_ptr<Brush> createBrush(cCore& core);

		virtual void onClose( tgui::Container& container );

		static std::string info();

		virtual bool hasBrushChanged();

	};
}
