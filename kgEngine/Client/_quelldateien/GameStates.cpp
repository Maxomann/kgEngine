#include "../GameState/GameStates.h"

namespace kg
{
	void TestGameState::onInit( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		//MenuBar
		m_menuBar = tgui::MenuBar::Ptr( gui );
		m_menuBar->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_menuBar->setSize( gui.getWindow()->getSize().x, 25 );
		m_menuBar->addMenu( editMenuName );
		m_menuBar->addMenuItem( editMenuName, editMenuTileItem );
		m_menuBar->addMenu( createMenuName );
		m_menuBar->addMenuItem( createMenuName, createMenuTileItem );
		m_menuBar->addMenu( connectionMenuName );
		m_menuBar->addMenuItem( connectionMenuName, connectionMenuConnectItem );
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
		for( auto it = begin( m_guiElements ); it != end( m_guiElements ); ++it)
			if( (*it)->shouldClose() )
				toBeRemoved.push_back( it );
		//erase elements
		for( const auto& el : toBeRemoved )
		{
			(*el)->onClose( gui );
			m_guiElements.erase( el );
		}


		bool mouseOnGui = false;
		for( const auto& widget : gui.getWidgets() )
			if( widget->isFocused() )
				mouseOnGui = true;

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
			return CLOSE_APP;
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Subtract ) )
			camera.zoom( 2 );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Add ) )
			camera.zoom( 0.5 );

		//movement
		sf::Vector2f movement;
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
				movement.y -= 100;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
				movement.y += 100;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
				movement.x -= 100;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
				movement.x += 100;
		}
		else
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
				movement.y -= 10;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
				movement.y += 10;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
				movement.x -= 10;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
				movement.x += 10;
		}
		//rotate and apply movement
		camera.moveCenter( sf::Vector2i( rotatePointAroundPoint( movement, camera.getRotation() ) ) );

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Q ) )
			camera.rotate( -5.0f );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::E ) )
			camera.rotate( 5.0f );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) )
		{
			camera.setCenter( sf::Vector2i( 0, 0 ) );
			world.reset();
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Z ) )
		{
			camera.setRotation( 0.0f );
			camera.setZoom( 1.0f );
		}
		if( !mouseOnGui )
		{

		}

		return m_nextGameState;
	}

	void TestGameState::onClose( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		REPORT_ERROR( "standart GameState should not be closed at the moment" );
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
			auto ptr = std::make_shared<TileDrawingWindow>();
			ptr->initExtensions( core.pluginManger );
			ptr->onInit( core, gui );
			m_guiElements.push_back( ptr );
		}
		if( callback.text == connectionMenuConnectItem )
		{
			auto ptr = std::make_shared<ConnectToServerWindow>();
			ptr->onInit( core, gui );
			m_guiElements.push_back( ptr );
		}
	}
}
