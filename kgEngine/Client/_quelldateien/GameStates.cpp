#include "../GameState/GameStates.h"

namespace kg
{
	void StandartGameState::onInit( World& world, Camera& camera, tgui::Gui& gui )
	{
		m_testbutton = tgui::Button::Ptr( gui );
		m_testbutton->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_testbutton->setPosition( 500, 500 );
		m_testbutton->setText( "Switch to editor mode" );
		m_testbutton->bindCallbackEx( std::bind(
			&StandartGameState::testbuttonCallback,
			this,
			std::placeholders::_1,
			std::ref(world),
			std::ref( camera),
			std::ref( gui )),
			tgui::Button::LeftMouseClicked );
	}

	void StandartGameState::handleEvent( sf::Event& sfmlEvent )
	{

	}

	int StandartGameState::frame( World& world, Camera& camera, tgui::Gui& gui )
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
			camera.setCenter( sf::Vector2i( 0, 0 ) );


		return m_nextGameState;
	}

	void StandartGameState::onClose( World& world, Camera& camera, tgui::Gui& gui )
	{
		REPORT_ERROR( "standart GameState should not be closed" );
	}

	int StandartGameState::getID() const
	{
		return GAME_STATE_ID::STANDART;
	}

	std::string StandartGameState::info() const
	{
		return "Standart GameState plugin";
	}

	void StandartGameState::testbuttonCallback( const tgui::Callback& callback, World& world, Camera& camera, tgui::Gui& gui )
	{
		if( callback.trigger == tgui::Button::LeftMouseClicked )
		{
			//switch to editor GameState here
		}
	}
}
