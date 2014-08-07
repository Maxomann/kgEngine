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
		/// List of states of the games.
		std::unordered_map<int, std::shared_ptr<GameState>> m_gameStates;

		/// The window.
		sf::RenderWindow									m_window;

		/// The graphical user interface.
		tgui::Gui                                           m_gui;

		/// The camera.
		Camera                                              m_camera;

		/// The world.
		World                                               m_world;

		/// The render distance in chunks.
		sf::IntRect                                         m_renderDistanceInChunks;

		/// State of the game.
		std::shared_ptr<GameState>                          m_gameState;

		/// true if this object is standart game state loaded.
		bool                                                m_isStandartGameStateLoaded = false;

		/// Initializes this object from configuration file. The information will be retrieved from
		/// the database.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @param	database	The database.
		void                                                m_initFromConfigFile( const ClientDatabase& database );

		/// Executes the configuration file modified action.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @param	callbackID	  	Identifier for the callback.
		/// @param	clientDatabase	The client database.
		void												m_onConfigFileModified( const int& callbackID, const ClientDatabase& clientDatabase );

	public:

		/// Default constructor.
		///
		/// @author	Kay
		/// @date	07.08.2014
		Client();

		/// Gets the world.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @return	The world.
		World& getWorld();

		/// Frames the given core.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @param [in,out]	core	The core.
		void frame( cCore& core );

		/// Gets the information.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @return	A std::string.
		virtual std::string info() const;

		/// Initialises the extensions.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @param [in,out]	pluginManager	Manager for plugin.
		virtual void initExtensions( pPluginManager& pluginManager );

		/// Executes the initialise action.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @param [in,out]	core	The core.
		virtual void onInit( cCore& core );

		/// Executes the close action.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @param [in,out]	core	The core.
		virtual void onClose( cCore& core );

		/// The configuration file path.
		static const char config_file_path[];
	};
}
