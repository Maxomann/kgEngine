//_______GAME_STATE_______//

#pragma once
#include "../stdafx.h"

#include "GameState.h"
#include "../GUI/GuiElements.h"

namespace kg
{
	class TestGameState : public GameState
	{
		tgui::MenuBar::Ptr m_menuBar=nullptr;
		tgui::ListBox::Ptr m_tileSelectionBox = nullptr;

// 		tgui::ChildWindow::Ptr m_connectToServerWindow = nullptr;
// 		tgui::EditBox::Ptr m_ctsIp = nullptr;
// 		tgui::EditBox::Ptr m_ctsRecievePortOnServer = nullptr;
// 		tgui::EditBox::Ptr m_ctsRecievePortOnClient = nullptr;
// 		tgui::Button::Ptr m_ctsSendButton = nullptr;

		std::list<std::unique_ptr<NonStaticGuiElement>> m_guiElements;

		int m_nextGameState = NO_CHANGE;


		void m_menuBarCallback( const tgui::Callback& callback, cCore& core, World& world, Camera& camera, tgui::Gui& gui );
		//void m_connectToServerWindowCallback( const tgui::Callback& callback, cCore& core, World& world, Camera& camera, tgui::Gui& gui );

	public:

		virtual void onInit( cCore& core, World& world, Camera& camera, tgui::Gui& gui );

		virtual void handleEvent( sf::Event& sfmlEvent );

		virtual int frame( cCore& core, sf::RenderWindow& window, World& world, Camera& camera, tgui::Gui& gui );

		virtual void onClose( cCore& core, World& world, Camera& camera, tgui::Gui& gui );

		virtual int getID() const;


		virtual std::string info() const;

	};


}
