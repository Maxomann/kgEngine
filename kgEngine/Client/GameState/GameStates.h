//_______GAME_STATE_______//

#pragma once
#include "../stdafx.h"

#include "GameState.h"

namespace kg
{
	class TestGameState : public GameState
	{
		tgui::ListBox::Ptr m_tileSelectionBox;
		tgui::MenuBar::Ptr m_menuBar;

		int m_nextGameState = NO_CHANGE;



		void switchToEditorButtonCallback( const tgui::Callback& callback, cCore& core, World& world, Camera& camera, tgui::Gui& gui );

	public:

		virtual void onInit( cCore& core, World& world, Camera& camera, tgui::Gui& gui );

		virtual void handleEvent( sf::Event& sfmlEvent );

		virtual int frame( cCore& core, World& world, Camera& camera, tgui::Gui& gui );

		virtual void onClose( cCore& core, World& world, Camera& camera, tgui::Gui& gui );

		virtual int getID() const;


		virtual std::string info() const;

	};
}
