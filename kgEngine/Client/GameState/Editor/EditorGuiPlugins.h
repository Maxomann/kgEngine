//_______GUI_PLUGINS_______//

#pragma once
#include "EditorGuiElements.h"

namespace kg
{
	class PointBrush : public Brush
	{
		//pair.first = chunkPosition; pair.second = relativeTilePosition
		std::vector< std::pair<sf::Vector2i, sf::Vector2i> > m_tilePositionsToSet;

		std::vector< sf::Sprite > m_previewTiles;

		int m_tileId;

	public:
		PointBrush( int selectedTileId )
			:m_tileId( selectedTileId )
		{ };

		virtual void apply( cCore& core,
							sf::Vector2i mousePositionInWorld,
							sf::Vector2i chunkPosition,
							sf::Vector2i relativeTilePosition )
		{
			Brush::apply( core, mousePositionInWorld, chunkPosition, relativeTilePosition );

			//if no position is to be set, no message has to be sended
			if (m_tilePositionsToSet.size()!=NULL)
			{
				std::vector< const sf::Vector2i > chunkPositions;
				std::vector< const sf::Vector2i > relativeTilePositions;
				std::vector< const int > tileIDs;
				for( const auto& el : m_tilePositionsToSet )
				{
					chunkPositions.push_back( el.first );
					relativeTilePositions.push_back( el.second );
					tileIDs.push_back( m_tileId );
				}
				core.networkManager.sendMessage( std::make_shared<SetTilesRequest>(
					chunkPositions,
					relativeTilePositions,
					tileIDs ),
					core.getServerIp(),
					core.getServerPort() );
			}
			
			m_previewTiles.clear();
			m_tilePositionsToSet.clear();
		}

		virtual void recalculatePreview( cCore& core,
										 sf::Vector2i mousePositionInWorld,
										 sf::Vector2i chunkPosition,
										 sf::Vector2i relativeTilePosition )
		{
			auto it = std::find(
				std::begin(m_tilePositionsToSet),
				std::end( m_tilePositionsToSet ),
				std::make_pair( chunkPosition, relativeTilePosition ) );

			if( it == std::end( m_tilePositionsToSet ) )
			{
				m_tilePositionsToSet.push_back( std::make_pair( chunkPosition, relativeTilePosition ) );

				m_previewTiles.emplace_back();
				m_previewTiles.back().setTexture( core.getExtension<ClientDatabase>()->getTileTexture( m_tileId ) );
				Animation animation( core.getExtension<ClientDatabase>()->getTile( m_tileId ) );
				animation.apply( m_previewTiles.back() );
				m_previewTiles.back().setPosition( sf::Vector2f( Chunk::getPositionInPixelForTile( chunkPosition, relativeTilePosition ) ) );
				//scale the sprite to fit the global Dimensions
			}
		}

		virtual void draw( Camera& camera )
		{
			for( auto& el : m_previewTiles )
				camera.draw( el, Camera::TILE_PREVIEW );
		}

		virtual void cancel()
		{
			Brush::cancel();
			m_previewTiles.clear();
			m_tilePositionsToSet.clear();
		}

	};

	class PointBrushSubWindow : public TileDrawingSubWindow
	{
		tgui::ListBox::Ptr m_tileSelectionBox;

		void m_refreshTileSelectonBox( cCore& core )
		{
			m_tileSelectionBox->addItem( "NONE" );
			for( const auto& el : core.getExtension<ClientDatabase>()->getTiles() )
				m_tileSelectionBox->addItem( el.second.tileName );
		};

		void m_callback( const tgui::Callback& callback )
		{
			m_hasBrushChanged = true;
		}

		bool m_hasBrushChanged = true;

	public:
		virtual void onInit( cCore& core, tgui::Container& container )
		{
			//TileSelectionBox
			m_tileSelectionBox = tgui::ListBox::Ptr( container );
			m_tileSelectionBox->setPosition( 20, 60 );
			m_tileSelectionBox->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
			m_tileSelectionBox->setSize( TileDrawingWindow::windowSize.x,
										 TileDrawingWindow::windowSize.y - TileDrawingWindow::selectionBarSize.y - 40 );
			m_tileSelectionBox->setPosition( 0, TileDrawingWindow::selectionBarSize.y + 20 );
			m_refreshTileSelectonBox(core);
			m_tileSelectionBox->setSelectedItem( NULL );
			m_tileSelectionBox->bindCallbackEx( std::bind( &PointBrushSubWindow::m_callback, this, std::placeholders::_1 ),
												tgui::ListBox::ItemSelected );
			//TileSelectionBox END
		};

		virtual std::unique_ptr<Brush> createBrush(cCore& core)
		{
			m_hasBrushChanged = false;

			std::string tileName = m_tileSelectionBox->getSelectedItem();
			if( tileName == "NONE" || m_tileSelectionBox->getSelectedItemId()<NULL )
				return nullptr;

			int tileId = core.getExtension<ClientDatabase>()->getTileID( tileName );

			return std::make_unique<PointBrush>( tileId );
		};

		virtual void onClose( tgui::Container& container )
		{
			container.remove( m_tileSelectionBox );
		};

		static std::string info()
		{
			return "PointBrush";
		};

		virtual bool hasBrushChanged()
		{
			return m_hasBrushChanged;
		}

	};
}
