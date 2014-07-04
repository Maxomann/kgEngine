//_______CLIENT_______//

#pragma once
#include "stdafx.h"
#include "Network/Messages.h"
#include "World/World.h"
#include "Drawing/Animation.h"
#include "GUI/GuiManager.h"
#include "GameState/GameStates.h"

namespace kg
{
	class Client : public cCoreExtension
	{
		std::unordered_map<int, std::shared_ptr<GameState>> m_gameStates;

		sf::RenderWindow m_window;

		tgui::Gui m_gui;
		Camera m_camera;
		World m_world;

		aDataByIdentifierFile m_config_file;

		std::shared_ptr<GameState> m_gameState;

		bool m_isStandartGameStateLoaded = false;

	public:
		Client();

		World& getWorld();

		void frame( cCore& core );

		virtual std::string info() const;

		virtual void initExtensions( pPluginManager& pluginManager );

		static const char config_file_path[];
	};
}
