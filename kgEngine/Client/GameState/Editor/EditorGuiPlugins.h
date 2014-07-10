//_______GUI_PLUGINS_______//

#pragma once
#include "EditorGuiElements.h"

namespace kg
{
	class PointBrush : public Brush
	{
	public:
		virtual void begin()
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

		virtual void apply()
		{
			throw std::logic_error( "The method or operation is not implemented." );

			//set the new tile
			// 			core.networkManager.sendMessage( std::make_shared<SetTileRequest>(
			// 				World::getAbsoluteChunkPosition( window, camera ),
			// 				World::getRelativeTilePosition( window, camera ), tileID ),
			// 				core.getServerIp(),
			// 				core.getServerPort() );
		}

		virtual void cancel()
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

		virtual void recalculatePreview( sf::Vector2i chunkPosition, sf::Vector2i relativeTilePosition )
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

		virtual void draw( Camera& camera )
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}
	};


	class PointBrushSubWindow : public TileDrawingSubWindow
	{
		tgui::ListBox::Ptr m_tileSelectionBox;

	public:
		virtual void onInit( cCore& core, tgui::Container& container )
		{
			//TileSelectionBox
			m_tileSelectionBox = tgui::ListBox::Ptr( container );
			m_tileSelectionBox->setPosition( 20, 60 );
			m_tileSelectionBox->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
			m_tileSelectionBox->setSize( TileDrawingWindow::windowSize.x,
										 TileDrawingWindow::windowSize.y-TileDrawingWindow::selectionBarSize.y-40 );
			m_tileSelectionBox->setPosition( 0, TileDrawingWindow::selectionBarSize.y+20 );
			m_tileSelectionBox->addItem( "NONE" );
			m_tileSelectionBox->setSelectedItem( NULL );
			//TileSelectionBox END
		};

		virtual std::shared_ptr<Brush> createBrush()
		{
			return std::make_shared<PointBrush>();
		};

		virtual void onClose( tgui::Container& container )
		{
			container.remove( m_tileSelectionBox );
		};

		static std::string info()
		{
			return "SingleBrush";
		};
	};
}
