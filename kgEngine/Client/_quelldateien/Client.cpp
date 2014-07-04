#include "../Client.h"

namespace kg
{
	const char kg::Client::config_file_path[] = "config_client.txt";

	kg::Client::Client()
		:m_gui( m_window )
	{
		m_config_file.loadFromFile( config_file_path );

		sf::ContextSettings contextSettings;
		contextSettings.antialiasingLevel = atoi( m_config_file.getData("Antialiasing").c_str() );

		//initialize the Client with the data from the config_file
		m_window.create( sf::VideoMode( std::atoi( m_config_file.getData( "resx" ).c_str() ), std::atoi( m_config_file.getData( "resy" ).c_str() ) ), m_config_file.getData( "window_name" ),
						 sf::Style::Titlebar|sf::Style::Close,
						 contextSettings );
		//camera
		m_camera.init( sf::Vector2u( std::atoi( m_config_file.getData( "resx" ).c_str() ), std::atoi( m_config_file.getData( "resy" ).c_str() ) ) );
		//vSynch
		if( m_config_file.getData( "vsynch" ) == "true" )
			m_window.setVerticalSyncEnabled( true );
		else
			m_window.setVerticalSyncEnabled( false );

		//init GUI
		if( !m_gui.setGlobalFont( resourceFolderPath + fontFolderName + "DejaVuSans.ttf" ) )
			REPORT_ERROR_FILEACCESS( resourceFolderPath + fontFolderName + "DejaVuSans.ttf" + "could not be loaded" );
	}

	void kg::Client::frame( cCore& core )
	{
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

			m_gui.handleEvent( event );
			m_gameState->handleEvent( event );
		}



		//Call frame() here:
		m_world.frame( core );
		// Ensure, that all chunks which can be seen on the camera, are loaded
		m_world.loadChunksInRectAndUnloadOther( core, { sf::IntRect( m_camera.getCameraRect() ) } );

		// change gameState if needed
		int newGameStateId = m_gameState->frame(core, m_window, m_world , m_camera , m_gui );
		if( newGameStateId == GameState::CLOSE_APP )
			core.close();
		else if( newGameStateId > -1 )
		{
			m_gameState->onClose(core, m_world, m_camera , m_gui );
			m_gameState = m_gameStates.at( newGameStateId );
		}



		//Camera drawing here:
		m_world.draw( m_camera );



		m_window.clear( sf::Color::Green );
		//window-drawing here:
		m_camera.display( m_window );
		m_gui.draw();
		m_window.display();
	}

	std::string kg::Client::info() const
	{
		return "Build-in CLIENT plugin";
	}

	kg::World& kg::Client::getWorld()
	{
		return m_world;
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
}
