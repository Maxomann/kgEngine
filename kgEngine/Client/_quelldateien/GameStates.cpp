#include "../GameState/GameStates.h"

namespace kg
{
	void TestGameState::onInit( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		//register m_onConfigFileModified callback
		core.getExtension<ClientDatabase>()->registerCallback(
			this,
			std::bind(
			&TestGameState::m_onConfigFileModified,
			this,
			std::placeholders::_1,
			std::placeholders::_2 ),
			CALLBACK_ID::CLIENT_DATABASE::CONFIG_FILE_MODIFIED );

		//MenuBar
		m_menuBar = tgui::MenuBar::Ptr( gui );
		m_menuBar->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_menuBar->setSize( gui.getWindow()->getSize().x, 25 );
		m_menuBar->addMenu( editMenuName );
		m_menuBar->addMenuItem( editMenuName, editMenuTileItem );
		m_menuBar->addMenuItem( editMenuName, editMenuSwitchFullscreenItem );
		m_menuBar->addMenu( createMenuName );
		m_menuBar->addMenuItem( createMenuName, createMenuTileItem );
		m_menuBar->addMenu( connectionMenuName );
		m_menuBar->addMenuItem( connectionMenuName, connectionMenuConnectItem );
		m_menuBar->addMenu( loadMenuName );
		m_menuBar->addMenuItem( loadMenuName, loadMenuAllItem );
		m_menuBar->addMenuItem( loadMenuName, loadMenuTilesItem );
		m_menuBar->addMenuItem( loadMenuName, loadMenuConfigItem );
		m_menuBar->addMenu( saveMenuName );
		m_menuBar->addMenuItem( saveMenuName, saveMenuAllItem );
		m_menuBar->addMenuItem( saveMenuName, saveMenuTilesItem );
		m_menuBar->addMenuItem( saveMenuName, saveMenuConfigItem );
		m_menuBar->bindCallbackEx( std::bind(
			&TestGameState::m_menuBarCallback,
			this,
			std::placeholders::_1,
			std::ref( core ),
			std::ref( gui ) ),
			tgui::MenuBar::MenuItemClicked );
		//MenuBar END
	}

	void TestGameState::handleEvent( sf::Event& sfmlEvent )
	{

	}

	int TestGameState::frame( cCore& core, sf::RenderWindow& window, World& world, Camera& camera, tgui::Gui& gui )
	{
		//check if GUI elements have to be removed
		std::vector<std::list<std::shared_ptr<NonStaticGuiElement>>::iterator> toBeRemoved;
		for( auto it = begin( m_guiElements ); it != end( m_guiElements ); ++it )
			if( (*it)->shouldClose() )
				toBeRemoved.push_back( it );
		//erase elements
		for( const auto& el : toBeRemoved )
		{
			//if element was referenced externally //FOR EVRY REFERENCED GUI-ELEMENT
			if( (*el) == r_tileDrawingWindow )
				r_tileDrawingWindow = nullptr;


			(*el)->onClose( gui.getContainer() );
			m_guiElements.erase( el );
		}

		//set the correct brush
		if( r_tileDrawingWindow )
		{
			if( r_tileDrawingWindow->hasBrushChanged() )
			{
				m_brush = r_tileDrawingWindow->getBrush( core );
			}
		}
		else
			m_brush = nullptr;


		bool mouseOnGui = false;
		for( const auto& widget : gui.getWidgets() )
			if( widget->isFocused() )
				mouseOnGui = true;
		auto mousePositionInWorld = World::getAbsoluteMousePosition( window, camera );
		auto chunkPosition = World::getAbsoluteChunkPosition( window, camera );
		auto relativeTilePosition = World::getRelativeTilePosition( window, camera );

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
			return CLOSE_APP;
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Subtract ) )
			camera.zoom( 1.1 );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Add ) )
			camera.zoom( 0.9 );

		//MOVEMENT
		sf::Vector2f movement(0,0);
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
				movement.y -= (100.0 / 60.0 * core.getFrameTimeInMilliseconds());
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
				movement.y += (100.0 / 60.0 * core.getFrameTimeInMilliseconds());
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
				movement.x -= (100.0 / 60.0 * core.getFrameTimeInMilliseconds());
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
				movement.x += (100.0 / 60.0 * core.getFrameTimeInMilliseconds());
		}
		else
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
				movement.y -= (10.0 / 60.0 * core.getFrameTimeInMilliseconds());
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
				movement.y += (10.0 / 60.0 * core.getFrameTimeInMilliseconds());
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
				movement.x -= (10.0 / 60.0 * core.getFrameTimeInMilliseconds());
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
				movement.x += (10.0 / 60.0 * core.getFrameTimeInMilliseconds());
		}
		movement /= camera.getZoom();
		//rotate and apply movement
		camera.moveCenter( sf::Vector2i( rotatePointAroundPoint( movement, camera.getRotation() ) ) );

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Q ) )
			camera.rotate( (-3.0 / 60.0 * core.getFrameTimeInMilliseconds()) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::E ) )
			camera.rotate( (3.0 / 60.0 * core.getFrameTimeInMilliseconds()) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::R )
			&& m_timeSinceLastResourceReload.getElapsedTime().asMilliseconds() > 200 )
		{
			world.reset();
			m_timeSinceLastResourceReload.restart();
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::P ) )
			camera.setCenter( sf::Vector2i( 0, 0 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Z ) )
		{
			camera.setRotation( 0.0f );
			camera.setZoom( 1.0f );
		}


		if( !mouseOnGui )
		{
			//BRUSH
			if( m_brush )
			{
				if( m_brush->isActive() )
				{
					if( sf::Mouse::isButtonPressed( sf::Mouse::Right ) )
						m_brush->cancel();
					else
					{
						m_brush->recalculatePreview( core, mousePositionInWorld, chunkPosition, relativeTilePosition );
						m_brush->draw( camera );
						if( !sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
							m_brush->apply( core, mousePositionInWorld, chunkPosition, relativeTilePosition );
					}
				}
				else
				{
					if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
						m_brush->begin( mousePositionInWorld, chunkPosition, relativeTilePosition );
				}
			}
		}

		return m_nextGameState;
	}

	void TestGameState::onClose( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		gui.remove( m_menuBar );
		for( const auto& el : m_guiElements )
			el->onClose( gui.getContainer() );
	}

	int TestGameState::getID() const
	{
		return GAME_STATE_ID::STANDART;
	}

	std::string TestGameState::info() const
	{
		return "Standart GameState plugin";
	}

	void TestGameState::m_menuBarCallback( const tgui::Callback& callback,
										   cCore& core,
										   tgui::Gui& gui )
	{
		if( callback.text == editMenuTileItem )
		{
			if( !r_tileDrawingWindow )
			{
				auto ptr = std::make_shared<TileDrawingWindow>();
				ptr->initExtensions( core.pluginManger );
				ptr->onInit( core, gui.getContainer() );
				m_guiElements.push_back( ptr );
				r_tileDrawingWindow = ptr;
			}
		}
		if( callback.text == editMenuSwitchFullscreenItem )
		{
			core.getExtension<ClientDatabase>()->setFullscreenEnabled( !core.getExtension<ClientDatabase>()->isFullscreenEnabled() );
		}
		if( callback.text == connectionMenuConnectItem )
		{
			auto ptr = std::make_shared<ConnectToServerWindow>();
			ptr->onInit( core, gui.getContainer() );
			m_guiElements.push_back( ptr );
		}
		if( callback.text == loadMenuAllItem )
		{
			core.getExtension<ClientDatabase>()->loadAllResources( core );
		}
		if( callback.text == loadMenuTilesItem )
		{
			core.getExtension<ClientDatabase>()->loadTiles( core );
		}
		if( callback.text == loadMenuConfigItem )
		{
			core.getExtension<ClientDatabase>()->loadConfigFile( core );
		}
		if( callback.text == saveMenuAllItem )
		{
			core.getExtension<ClientDatabase>()->saveAllResources();
		}
		if( callback.text == saveMenuTilesItem )
		{
			core.getExtension<ClientDatabase>()->saveTiles();
		}
		if( callback.text == saveMenuConfigItem )
		{
			core.getExtension<ClientDatabase>()->saveConfigFile();
		}
	}

	void TestGameState::m_onConfigFileModified( const int& callbackID,
												const ClientDatabase& clientDatabase )
	{
		auto res = clientDatabase.getWindowResolution();
		m_menuBar->setSize( res.x, m_menuBar->getSize().y );
	}

}
