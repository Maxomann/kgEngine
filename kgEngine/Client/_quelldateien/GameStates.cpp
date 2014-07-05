#include "../GameState/GameStates.h"

namespace kg
{
	void TestGameState::onInit( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		//TileSelectionBox
		m_tileSelectionBox = tgui::ListBox::Ptr( gui );
		m_tileSelectionBox->setPosition( 20, 60 );
		m_tileSelectionBox->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_tileSelectionBox->setSize( 200, 100 );
		//load tile names from files
		m_tileSelectionBox->addItem( "NONE" );
		TileSettings* tileSettings;
		for( int id = 0; true; ++id )
		{
			try
			{
				tileSettings = &core.resourceManagement.getResourceFromResourceFolderForTile<TileSettings>( id, informationFileExtension );
			}
			catch( std::exception& e )
			{
				break;
			}
			m_tileSelectionBox->addItem( tileSettings->tileName );
		}
		m_tileSelectionBox->setSelectedItem( NULL );
		m_tileSelectionBox->hide();


		//MenuBar
		m_menuBar = tgui::MenuBar::Ptr( gui );
		m_menuBar->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_menuBar->setSize( gui.getWindow()->getSize().x, 25 );
		m_menuBar->addMenu( tileMenuName );
		m_menuBar->addMenuItem( tileMenuName, tileMenuEditTilesItem );
		m_menuBar->addMenu( connectionMenuName );
		m_menuBar->addMenuItem( connectionMenuName, connectionMenuConnectItem );
		m_menuBar->bindCallbackEx( std::bind(
			&TestGameState::m_menuBarCallback,
			this,
			std::placeholders::_1,
			std::ref( core ),
			std::ref( world ),
			std::ref( camera ),
			std::ref( gui ) ),
			tgui::MenuBar::MenuItemClicked );


		//ConnectToServerWindow
		m_connectToServerWindow = tgui::ChildWindow::Ptr( gui );
		m_connectToServerWindow->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_connectToServerWindow->setTitle( connectionMenuConnectItem );
		m_connectToServerWindow->setSize( 300, 200 );
		m_connectToServerWindow->keepInParent( true );
		m_connectToServerWindow->bindCallbackEx( std::bind(
			&TestGameState::m_connectToServerWindowCallback,
			this,
			std::placeholders::_1,
			std::ref( core ),
			std::ref( world ),
			std::ref( camera ),
			std::ref( gui ) ),
			tgui::ChildWindow::Closed );

		m_ctsIp = tgui::EditBox::Ptr( *m_connectToServerWindow );
		m_ctsIp->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_ctsRecievePortOnClient = tgui::EditBox::Ptr( *m_connectToServerWindow );
		m_ctsRecievePortOnClient->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_ctsRecievePortOnServer = tgui::EditBox::Ptr( *m_connectToServerWindow );
		m_ctsRecievePortOnServer->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_ctsSendButton = tgui::Button::Ptr( *m_connectToServerWindow );
		m_ctsSendButton->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );

		m_ctsIp->setText( sf::IpAddress::getPublicAddress().toString() );
		m_ctsIp->setSize( 300, 50 );

		m_ctsRecievePortOnClient->setText( "RecievePortOnClient" );
		m_ctsRecievePortOnClient->setSize( 300, 50 );
		m_ctsRecievePortOnClient->setPosition( 0, 50 );
		m_ctsRecievePortOnServer->setText( "RecievePortOnServer" );
		m_ctsRecievePortOnServer->setSize( 300, 50 );
		m_ctsRecievePortOnServer->setPosition( 0, 100 );

		m_ctsSendButton->setText( "Connect" );
		m_ctsSendButton->setPosition( 0, 150 );
		m_ctsSendButton->setSize( 300, 50 );
		m_ctsSendButton->bindCallbackEx( std::bind(
			&TestGameState::m_connectToServerWindowCallback,
			this,
			std::placeholders::_1,
			std::ref( core ),
			std::ref( world ),
			std::ref( camera ),
			std::ref( gui ) ),
			tgui::Button::LeftMouseClicked );

		m_connectToServerWindow->hide();

	}

	void TestGameState::handleEvent( sf::Event& sfmlEvent )
	{

	}

	int TestGameState::frame( cCore& core, sf::RenderWindow& window, World& world, Camera& camera, tgui::Gui& gui )
{
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
		camera.moveCenter( sf::Vector2i( rotatePointAroundPoint(movement, camera.getRotation()) ) );

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
			if( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) )
			{
				int selectedItemIndex = m_tileSelectionBox->getSelectedItemIndex();
				//if no item is selected, select item: NONE
				if( selectedItemIndex < 0 )
					m_tileSelectionBox->setSelectedItem( NULL );
				else if( selectedItemIndex != NULL )
				{

					int tileID = selectedItemIndex - 1;

					//set the new tile
					core.networkManager.sendMessage( std::make_shared<SetTileRequest>(
						World::getAbsoluteChunkPosition( window, camera ),
						World::getRelativeTilePosition( window, camera ), tileID ),
						core.getServerIp(),
						core.getServerPort() );
				}
			}
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
										   World& world,
										   Camera& camera,
										   tgui::Gui& gui )
	{
		if( callback.text == tileMenuEditTilesItem )
		{
			if( m_tileSelectionBox->isVisible() )
				m_tileSelectionBox->hide();
			else
				m_tileSelectionBox->show();

			m_tileSelectionBox->setSelectedItem( NULL );
		}
		if( callback.text == connectionMenuConnectItem )
		{
			if( m_connectToServerWindow->isVisible() )
				m_connectToServerWindow->hide();
			else
				m_connectToServerWindow->show();
		}
	}

	void TestGameState::m_connectToServerWindowCallback( const tgui::Callback& callback,
														 cCore& core,
														 World& world,
														 Camera& camera,
														 tgui::Gui& gui )
	{
		if( callback.widget == &*m_connectToServerWindow )
		{
			m_connectToServerWindow->hide();
		}
		if( callback.widget == &*m_ctsSendButton )
		{
			sf::IpAddress ip( sf::IpAddress( m_ctsIp->getText() ) );
			sf::Uint16 recievePortOnServer(
				std::atoi( m_ctsRecievePortOnServer->getText().toAnsiString().c_str() ) );
			sf::Uint16 recievePortOnClient(
				std::atoi( m_ctsRecievePortOnClient->getText().toAnsiString().c_str() ) );

			core.networkManager.clearConnections();

			core.networkManager.addConnection( ip, recievePortOnClient, recievePortOnServer );

			core.networkManager.sendMessage(
				std::make_shared<ConnectionRequest>( recievePortOnClient, recievePortOnServer ),
				ip,
				standartServerRecievePort );
		}
	}

}
