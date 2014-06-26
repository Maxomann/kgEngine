#include "../GameState/GameStates.h"

namespace kg
{
	void StandartGameState::onInit( World& world, Camera& camera, tgui::Gui& gui )
	{
		throw std::logic_error( "The method or operation is not implemented." );
	}

	void StandartGameState::handleEvent( sf::Event& sfmlEvent )
	{
		throw std::logic_error( "The method or operation is not implemented." );
	}

	int StandartGameState::frame( World& world, Camera& camera, tgui::Gui& gui )
	{
		throw std::logic_error( "The method or operation is not implemented." );
	}

	void StandartGameState::onClose( World& world, Camera& camera, tgui::Gui& gui )
	{
		throw std::logic_error( "The method or operation is not implemented." );
	}

	int StandartGameState::getID() const
	{
		return GAME_STATE_ID::STANDART;
	}

	std::string StandartGameState::info() const
	{
		throw std::logic_error( "The method or operation is not implemented." );
	}

}
