//_______GUI_MANAGER_______//

#pragma once
#include "../stdafx.h"

namespace kg
{
	class Camera;
	class World;

	class GuiElement : public pExtension
	{
		World& r_world;

	public:
		GuiElement( World& world )
			:r_world(world)
		{ };

		virtual void create( tgui::Gui& gui ) = 0;
		virtual void destroy( tgui::Gui& gui ) = 0;

		virtual void frame() = 0;
		virtual void draw( Camera& camera ) = 0;

		virtual void callbackHandler() = 0;

		//returns the gui-state(s) in which this element should be active
		virtual std::vector<int> getActiveStates()const;
	};

	class GuiManager : public pExtendable
	{
		tgui::Gui m_gui;

	public:
		GuiManager( sf::RenderWindow& window );

		void setGuiState( int stateID );

		void passEvent( sf::Event& sfmlEvent );

		void frame();
		void drawToCam( Camera& camera );
		void drawToWindow();

		virtual void initExtensions()override;

	};
}
