//_______GAME_STATE_______//

#pragma once
#include "../stdafx.h"

#include "GameState.h"
#include "Editor/EditorGuiElements.h"

namespace kg
{
	class TestGameState : public GameState
	{
		tgui::MenuBar::Ptr                              m_menuBar = nullptr;

		std::list<std::shared_ptr<NonStaticGuiElement>> m_guiElements;
		std::shared_ptr<TileDrawingWindow>              m_tileDrawingWindow = nullptr;

		std::unique_ptr<Brush>                          m_brush = nullptr;

		int                                             m_nextGameState = NO_CHANGE;

		void m_menuBarCallback( const tgui::Callback& callback, cCore& core, tgui::Gui& gui );

	public:

		virtual void        onInit( cCore& core, World& world, Camera& camera, tgui::Gui& gui );

		virtual void        handleEvent( sf::Event& sfmlEvent );

		virtual int         frame( cCore& core, sf::RenderWindow& window, World& world, Camera& camera, tgui::Gui& gui );

		virtual void        onClose( cCore& core, World& world, Camera& camera, tgui::Gui& gui );

		virtual int         getID() const;

		virtual std::string info() const;
	};
}
