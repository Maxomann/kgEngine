#include "../Client.h"

const char kg::Client::config_file_path[] = "config_client.txt";

kg::Client::Client()
{
	m_config_file.loadFromFile( config_file_path );

	//initialize the Client with the data from the config_file
	m_window.create( sf::VideoMode( std::atoi( m_config_file.getData( "resx" ).c_str() ), std::atoi( m_config_file.getData( "resy" ).c_str() ) ), m_config_file.getData( "window_name" ) );
	//vSynch
	if( m_config_file.getData( "vsynch" ) == "true" )
		m_window.setVerticalSyncEnabled( true );
	else
		m_window.setVerticalSyncEnabled( false );

	m_resourceManagement.getResourceFromResourceFolder<ConfiguratedTexture>( "testimage.png" ).applyToSprite( m_sprite );
}

void kg::Client::frame( cCore& core, nNetworkManager& networkManger )
{
	networkManger.sendMessage( std::make_shared<ChunkDataRequest>( sf::Vector2i( 0, 0 ) ), sf::IpAddress::getLocalAddress(), 42000 );

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
		core.close();

	sf::Event event;
	while( m_window.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed )
			core.close();
	}

	m_window.clear( sf::Color::Green );
	//Do the Drawing inbetween here!
	m_window.draw( m_sprite );

	m_window.display();
}

std::string kg::Client::info() const
{
	return "Build-in CLIENT plugin";
}
