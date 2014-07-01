#include "../GameState/GameStates.h"

namespace kg
{
	void TestGameState::onInit( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		//TileSelectionBox
		m_tileSelectionBox = tgui::ListBox::Ptr( gui );
		m_tileSelectionBox->setPosition( 20, 40 );
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


		//MenuBar
		m_menuBar = tgui::MenuBar::Ptr( gui );
		m_menuBar->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_menuBar->setSize( gui.getWindow()->getSize().x, 20 );

	}

	void TestGameState::handleEvent( sf::Event& sfmlEvent )
	{

	}

	int TestGameState::frame( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		bool mouseOnGui = false;
		


		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
			return CLOSE_APP;
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Subtract ) )
			camera.zoom( 2 );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Add ) )
			camera.zoom( 0.5 );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
				camera.moveCenter( sf::Vector2i( 0, -100 ) );
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
				camera.moveCenter( sf::Vector2i( 0, 100 ) );
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
				camera.moveCenter( sf::Vector2i( -100, 0 ) );
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
				camera.moveCenter( sf::Vector2i( 100, 0 ) );
		}
		else
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
				camera.moveCenter( sf::Vector2i( 0, -10 ) );
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
				camera.moveCenter( sf::Vector2i( 0, 10 ) );
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
				camera.moveCenter( sf::Vector2i( -10, 0 ) );
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
				camera.moveCenter( sf::Vector2i( 10, 0 ) );
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) )
			camera.setCenter( sf::Vector2i( 0, 0 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Z ) )
			camera.setZoom( 1.0f );
		if( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) )
		{
			int selectedItemIndex = m_tileSelectionBox->getSelectedItemIndex();
			//if no item is selected, select item: NONE
			if(selectedItemIndex<0)
				m_tileSelectionBox->setSelectedItem( NULL );
			else if( selectedItemIndex != NULL )
			{   

				int tileID = selectedItemIndex - 1;

				//set the new tile
				core.networkManager.sendMessage( std::make_shared<SetTileRequest>(
					World::getAbsoluteChunkPosition(*gui.getWindow(), camera),
					World::getRelativeTilePosition( *gui.getWindow(), camera), tileID ),
					core.getServerIp(),
					core.getServerPort() );
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

	void TestGameState::switchToEditorButtonCallback( const tgui::Callback& callback, cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{

	}
}
