//_______CLIENT_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class Client : public cCoreExtension
	{
		sf::RenderWindow m_window;

		aDataByIdentifierFile m_config_file;

	public:
		Client()
		{
			m_config_file.loadFromFile( config_file_path );

			//initialize the Client with the data from the config_file
			m_window.create( sf::VideoMode( std::atoi( m_config_file.getData( "resx" ).c_str() ), std::atoi( m_config_file.getData( "resy" ).c_str() ) ), m_config_file.getData( "window_name" ) );
			//vSynch
			if( m_config_file.getData( "vsynch" ) == "true" )
				m_window.setVerticalSyncEnabled( true );
			else
				m_window.setVerticalSyncEnabled( false );
		}

		virtual void frame( cCore& core, nNetworkManager& networkManger )
		{
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
			m_window.display();
			
		}

		virtual std::string info() const
		{
			return "Build in CLIENT plugin";
		}


		static const char config_file_path[];
	};
	const char Client::config_file_path[] = "config_client.txt";
}
