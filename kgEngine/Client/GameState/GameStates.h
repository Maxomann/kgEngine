//_______GAME_STATE_______//

#pragma once
#include "../stdafx.h"

#include "GameState.h"

namespace kg
{
	class StandartGameState : public GameState
	{
		tgui::Button::Ptr m_testbutton;

		void testbuttonCallback( const tgui::Callback& callback, World& world, Camera& camera, tgui::Gui& gui );

		int m_nextGameState = NO_CHANGE;

	public:

		virtual void onInit( World& world, Camera& camera, tgui::Gui& gui );

		virtual void handleEvent( sf::Event& sfmlEvent );

		virtual int frame( World& world, Camera& camera, tgui::Gui& gui );

		virtual void onClose( World& world, Camera& camera, tgui::Gui& gui );

		virtual int getID() const;


		virtual std::string info() const;

	};
}
