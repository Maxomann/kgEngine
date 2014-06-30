#include "../GameState/GameStates.h"

namespace kg
{
	void StandartGameState::onInit( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		m_tileSelectionBox = tgui::ListBox::Ptr( gui );
		m_tileSelectionBox->setPosition( 20, 20 );
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
	}

	void StandartGameState::handleEvent( sf::Event& sfmlEvent )
	{

	}

	int StandartGameState::frame( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
			return CLOSE_APP;
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Subtract ) )
			camera.zoom( 2 );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Add ) )
			camera.zoom( 0.5 );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
			camera.moveCenter( sf::Vector2i( 0, -10 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
			camera.moveCenter( sf::Vector2i( 0, 10 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
			camera.moveCenter( sf::Vector2i( -10, 0 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
			camera.moveCenter( sf::Vector2i( 10, 0 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) )
		{
			camera.setCenter( sf::Vector2i( 0, 0 ) );
			camera.setZoom( 1.0f );
		}
		if( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) )
		{
			int selectedItemIndex = m_tileSelectionBox->getSelectedItemIndex();
			//if no item is selected, select item: NONE
			if(selectedItemIndex==-2)
				m_tileSelectionBox->setSelectedItem( NULL );
			if( selectedItemIndex != NULL )
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

	void StandartGameState::onClose( cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{
		REPORT_ERROR( "standart GameState should not be closed at the moment" );
	}

	int StandartGameState::getID() const
	{
		return GAME_STATE_ID::STANDART;
	}

	std::string StandartGameState::info() const
	{
		return "Standart GameState plugin";
	}

	void StandartGameState::switchToEditorButtonCallback( const tgui::Callback& callback, cCore& core, World& world, Camera& camera, tgui::Gui& gui )
	{

	}
}
