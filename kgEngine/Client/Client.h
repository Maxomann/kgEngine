//_______CLIENT_______//

#pragma once
#include "stdafx.h"
#include "Network/Messages.h"
#include "World/World.h"
#include "Drawing/Animation.h"
#include "GameState/GameStates.h"
#include "ClientDatabase.h"

namespace kg
{
	class Client : public cCoreExtension, public aCallbackReciever
	{
		std::unordered_map<int, std::shared_ptr<GameState>> m_gameStates;

		sf::RenderWindow                                    m_window;

		tgui::Gui                                           m_gui;
		Camera                                              m_camera;
		World                                               m_world;

		sf::IntRect                                         m_renderDistaceInChunks;

		std::shared_ptr<GameState>                          m_gameState;

		bool                                                m_isStandartGameStateLoaded = false;

		sf::Clock                                           m_frameTimeClock;

		void                                                m_initFromConfigFile( const ClientDatabase& database );
		void												m_onConfigFileModified( const int& callbackID, const ClientDatabase& clientDatabase );

	public:
		Client();

		World& getWorld();

		void frame( cCore& core );

		virtual std::string info() const;

		virtual void initExtensions( pPluginManager& pluginManager );

		virtual void onInit( cCore& core );

		virtual void onClose( cCore& core );

		static const char config_file_path[];
	};
}
