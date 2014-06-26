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
		virtual void onInit( World& world, Camera& camera, tgui::Gui& gui ) = 0;

		virtual void handleEvent( sf::Event& sfmlEvent )=0;

		// return ID of a GameState to replace this GameState with GameState(id)
		//		onClose will get called
		virtual int frame( World& world, Camera& camera, tgui::Gui& gui )=0;

		virtual void onClose( World& world, Camera& camera, tgui::Gui& gui )=0;

		virtual int getID()const=0;
	};
}
