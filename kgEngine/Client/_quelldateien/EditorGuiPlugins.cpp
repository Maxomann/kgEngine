#include "../GameState/Editor/EditorGuiPlugins.h"

namespace kg
{


	PointBrush::PointBrush( int selectedTileId ) :m_tileId( selectedTileId )
	{

	}

	void PointBrush::apply( cCore& core, sf::Vector2i mousePositionInWorld, sf::Vector2i chunkPosition, sf::Vector2i relativeTilePosition )
	{
		Brush::apply( core, mousePositionInWorld, chunkPosition, relativeTilePosition );

		//if no position is to be set, no message has to be sended
		if( m_tilePositionsToSet.size() != NULL )
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

	void PointBrush::recalculatePreview( cCore& core, sf::Vector2i mousePositionInWorld, sf::Vector2i chunkPosition, sf::Vector2i relativeTilePosition )
	{
		auto it = std::find(
			std::begin( m_tilePositionsToSet ),
			std::end( m_tilePositionsToSet ),
			std::make_pair( chunkPosition, relativeTilePosition ) );

		if( it == std::end( m_tilePositionsToSet ) )
		{
			m_tilePositionsToSet.push_back( std::make_pair( chunkPosition, relativeTilePosition ) );

			m_previewTiles.emplace_back();
			m_previewTiles.back().setTexture( core.getExtension<ClientDatabase>()->getTileTexture( m_tileId ) );
			Animation animation( core.getExtension<ClientDatabase>()->getTile( m_tileId ) );
			Tile::scaleSpriteToGlobalTileDimensions( m_previewTiles.back(), animation );
			animation.apply( m_previewTiles.back() );
			m_previewTiles.back().setPosition( sf::Vector2f( Chunk::getPositionInPixelForTile( chunkPosition, relativeTilePosition ) ) );
			//scale the sprite to fit the global Dimensions
		}
	}

	void PointBrush::draw( Camera& camera )
	{
		for( auto& el : m_previewTiles )
			camera.draw( el, Camera::TILE_PREVIEW );
	}

	void PointBrush::cancel()
	{
		Brush::cancel();
		m_previewTiles.clear();
		m_tilePositionsToSet.clear();
	}


	void PointBrushSubWindow::m_refreshTileSelectonBox( cCore& core )
	{
		m_tileSelectionBox->addItem( "NONE" );
		for( const auto& el : core.getExtension<ClientDatabase>()->getTiles() )
			m_tileSelectionBox->addItem( el.second.tileName );
	}

	void PointBrushSubWindow::m_callback( const tgui::Callback& callback )
	{
		m_hasBrushChanged = true;
	}

	void PointBrushSubWindow::onInit( cCore& core, tgui::Container& container )
	{
		//TileSelectionBox
		m_tileSelectionBox = tgui::ListBox::Ptr( container );
		m_tileSelectionBox->setPosition( 20, 60 );
		m_tileSelectionBox->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_tileSelectionBox->setSize( TileDrawingWindow::windowSize.x,
									 TileDrawingWindow::windowSize.y - TileDrawingWindow::selectionBarSize.y - 40 );
		m_tileSelectionBox->setPosition( 0, TileDrawingWindow::selectionBarSize.y + 20 );
		m_refreshTileSelectonBox( core );
		m_tileSelectionBox->setSelectedItem( NULL );
		m_tileSelectionBox->bindCallbackEx( std::bind( &PointBrushSubWindow::m_callback, this, std::placeholders::_1 ),
											tgui::ListBox::ItemSelected );
		//TileSelectionBox END
	}

	std::unique_ptr<Brush> PointBrushSubWindow::createBrush( cCore& core )
	{
		m_hasBrushChanged = false;

		std::string tileName = m_tileSelectionBox->getSelectedItem();
		if( tileName == "NONE" || tileName == "" || m_tileSelectionBox->getSelectedItemId() < NULL )
			//if no field is selected
			return nullptr;

		int tileId = core.getExtension<ClientDatabase>()->getTileID( tileName );

		return std::make_unique<PointBrush>( tileId );
	}

	void PointBrushSubWindow::onClose( tgui::Container& container )
	{
		container.remove( m_tileSelectionBox );
	}

	std::string PointBrushSubWindow::info()
	{
		return "PointBrush";
	}

	bool PointBrushSubWindow::hasBrushChanged()
	{
		return m_hasBrushChanged;
	}

}
