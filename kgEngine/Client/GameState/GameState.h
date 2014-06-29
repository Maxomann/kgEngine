//_______GAME_STATE_______//

#pragma once
#include "../stdafx.h"

#include "../World/World.h"
#include "../Network/Messages.h"

namespace kg
{

	class GameState : public pExtension
	{
	public:
		virtual void onInit( cCore& core, World& world, Camera& camera, tgui::Gui& gui ) = 0;

		virtual void handleEvent( sf::Event& sfmlEvent )=0;

		// return ID of a GameState to replace this GameState with GameState(id)
		//		onClose will get called
		//		return -1 NO_CHANGE to keep this GameState
		//		return -2 CLOSE_APP to close the application
		virtual int frame( cCore& core, World& world, Camera& camera, tgui::Gui& gui )=0;

		static const int NO_CHANGE = -1;
		static const int CLOSE_APP = -2;

		virtual void onClose( cCore& core, World& world, Camera& camera, tgui::Gui& gui )=0;

		virtual int getID()const=0;
	};
}
