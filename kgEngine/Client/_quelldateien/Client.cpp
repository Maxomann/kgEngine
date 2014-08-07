#include "../Client.h"

namespace kg
{
	const char Client::config_file_path[] = "config_client.txt";

	Client::Client()
		:m_gui( m_window )
	{ }

	void Client::onInit( cCore& core )
	{
		auto database = core.getExtension<ClientDatabase>();
		database->loadAllResources( core );

		m_world.onInit( core );

		m_initFromConfigFile( *database );

		//init GUI
		if( !m_gui.setGlobalFont( resourceFolderPath + fontFolderName + "DejaVuSans.ttf" ) )
			REPORT_ERROR_FILEACCESS( resourceFolderPath + fontFolderName + "DejaVuSans.ttf" + "could not be loaded" );

		//register m_onConfigFileModified callback
		database->registerCallback(
			this,
			std::bind(
			&Client::m_onConfigFileModified,
			this,
			std::placeholders::_1,
			std::placeholders::_2 ),
			CALLBACK_ID::CLIENT_DATABASE::CONFIG_FILE_MODIFIED );
	}

	kg::World& Client::getWorld()
	{
		return m_world;
	}

	std::string Client::info() const
	{
		return "Build-in CLIENT plugin";
	}

	void Client::frame( cCore& core )
	{
		auto frameTime = core.getFrameTimeInMilliseconds();
		m_window.setTitle( core.getExtension<ClientDatabase>()->getWindowName() + " --- FrameTime: " + std::to_string( frameTime ) );

		if( !m_isStandartGameStateLoaded )
		{
			//set standart gameState
			m_gameState = m_gameStates.at( GAME_STATE_ID::STANDART );
			m_gameState->onInit( core, m_world, m_camera, m_gui );
			m_isStandartGameStateLoaded = true;
		}

		//SFML loop:
		sf::Event event;
		while( m_window.pollEvent( event ) )
		{
			if( event.type == sf::Event::Closed )
				core.close();

			if( event.type == sf::Event::Resized )
				core.getExtension<ClientDatabase>()->setWindowResolution( sf::Vector2i( event.size.width, event.size.height ) );

			m_gui.handleEvent( event );
			m_gameState->handleEvent( event );
		}

		// change gameState if needed
		int newGameStateId = m_gameState->frame( core, m_window, m_world, m_camera, m_gui );
		if( newGameStateId == GameState::CLOSE_APP )
			core.close();
		else if( newGameStateId > GameState::NO_CHANGE )
		{
			m_gameState->onClose( core, m_world, m_camera, m_gui );
			m_gameState = m_gameStates.at( newGameStateId );
		}

		//apply render distance; unload all chunks that are not in it
		auto chunkRenderRect = m_renderDistanceInChunks;
		auto offset = m_camera.getCenter();
		chunkRenderRect.left += offset.x;
		chunkRenderRect.top += offset.y;
		m_world.loadChunksInRectAndUnloadOther( core, { chunkRenderRect } );

		//Call frame() here:
		m_world.frame( core );

		//Camera drawing here:
		m_world.draw( m_camera );

		m_window.clear( sf::Color::Green );
		//window-drawing here:
		m_camera.display( m_window );
		m_gui.draw();
		m_window.display();
	}
	void Client::initExtensions( pPluginManager& pluginManager )
	{
		pluginManager.fillExtandable<Client>( *this );

		for( const auto& el : m_extensions )
		{
			auto ptr = std::dynamic_pointer_cast< GameState >(el.second);
			if( ptr )
			{
				m_gameStates[ptr->getID()] = ptr;
			}
		}
	}

	void Client::onClose( cCore& core )
	{
		core.getExtension<ClientDatabase>()->saveAllResources();
	}

	void Client::m_initFromConfigFile( const ClientDatabase& database )
	{
		m_gui.setWindow( m_window );

		sf::ContextSettings contextSettings;
		contextSettings.antialiasingLevel = database.getAntialiasingLevel();

		if( database.isFullscreenEnabled() )
		{
			//initialize the Client with the data from the config_file
			m_window.create( sf::VideoMode( database.getWindowResolution().x, database.getWindowResolution().y ),
							 database.getWindowName(),
							 sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen,
							 contextSettings );
		}
		else
		{
			//initialize the Client with the data from the config_file
			m_window.create( sf::VideoMode( database.getWindowResolution().x, database.getWindowResolution().y ),
							 database.getWindowName(),
							 sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize,
							 contextSettings );
		}

		//vSynch
		m_window.setVerticalSyncEnabled( database.isVsynchEnabled() );
		//camera
		m_camera.init( sf::Vector2u( m_window.getSize() ) );
		//renderDistance
		sf::Vector2i renderDistance = database.getRenderDistance();
		m_renderDistanceInChunks.left = -renderDistance.x*chunkSizeInTiles*tileSizeInPixel;
		m_renderDistanceInChunks.top = -renderDistance.y*chunkSizeInTiles*tileSizeInPixel;
		m_renderDistanceInChunks.width = renderDistance.x * 2 * chunkSizeInTiles*tileSizeInPixel;
		m_renderDistanceInChunks.height = renderDistance.y * 2 * chunkSizeInTiles*tileSizeInPixel;

	}

	void Client::m_onConfigFileModified( const int& callbackID, const ClientDatabase& clientDatabase )
	{
		m_initFromConfigFile( clientDatabase );
	}
}
