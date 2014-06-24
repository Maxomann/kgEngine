#include "../Client.h"

namespace kg
{

	const char kg::Client::config_file_path[] = "config_client.txt";

	kg::Client::Client( pPluginManager& pluginManger )
		:m_guiManager(m_window)
	{
		m_config_file.loadFromFile( config_file_path );

		//initialize the Client with the data from the config_file
		m_window.create( sf::VideoMode( std::atoi( m_config_file.getData( "resx" ).c_str() ), std::atoi( m_config_file.getData( "resy" ).c_str() ) ), m_config_file.getData( "window_name" ) );
		//camera
		m_camera.init( sf::Vector2u( std::atoi( m_config_file.getData( "resx" ).c_str() ), std::atoi( m_config_file.getData( "resy" ).c_str() ) ) );
		//vSynch
		if( m_config_file.getData( "vsynch" ) == "true" )
			m_window.setVerticalSyncEnabled( true );
		else
			m_window.setVerticalSyncEnabled( false );


		//GuiElements laden
		pluginManger.fillExtandable<GuiManager>( m_guiManager );
		m_guiManager.initExtensions();
		m_guiManager.setGuiState( GUI_STATE::DEFAULT );
	}

	void kg::Client::frame( cCore& core )
	{

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
			core.close();
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Subtract ) )
			m_camera.zoom( 2 );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Add ) )
			m_camera.zoom( 0.5 );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
			m_camera.moveCenter( sf::Vector2i( 0, -10 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
			m_camera.moveCenter( sf::Vector2i( 0, 10 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
			m_camera.moveCenter( sf::Vector2i( -10, 0 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
			m_camera.moveCenter( sf::Vector2i( 10, 0 ) );
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) )
			m_camera.setCenter( sf::Vector2i(0, 0) );


		//SFML loop:
		sf::Event event;
		while( m_window.pollEvent( event ) )
		{
			if( event.type == sf::Event::Closed )
				core.close();

			m_guiManager.passEvent( event );
		}


		//Call frame() here:
		m_world.frame( core );
		// Ensure, that all chunks which can be seen on the camera, are loaded
		m_world.loadChunksInRectAndUnloadOther( core, { sf::IntRect( m_camera.getCameraRect() ) } );
		m_guiManager.frame();



		//Camera drawing here:
		m_world.draw( m_camera );
		m_guiManager.drawToCam( m_camera );


		m_window.clear( sf::Color::Green );
		//window-drawing here:
		m_camera.display( m_window );
		m_guiManager.drawToWindow();
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

}
