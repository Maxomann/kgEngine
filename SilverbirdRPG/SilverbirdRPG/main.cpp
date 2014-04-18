//_______MAIN_CPP_______//

#pragma once
#include "stdafx.h"
#include "SyncTime.h"
#include "ResourceManagement.h"
#include "nMessageServer.h"
#include "cCamera.h"
#include "cClient.h"
#include "sServer.h"
#include "aException.h"
#include "eExtendable.h"
#include "ksScript.h"

using namespace std;
using namespace kg;

int foo( const std::string& something )
{
	return 6;
}

class Bar
{
public:
	double doSomething( int a )
	{
		return 5.65324643 + (double)a;
	}
};

int main()
{
	try
	{
		ksLibrary lib;
		ksRegisterStandartTypes( lib );

		for( const auto&el : ksCode::generateSplitCode( lib.rawTokens, "function(int a, bool b){const std::string str = \"Hallo\";}" ) )
			cout << el.first << endl;
		

		system( "pause" );

		//Plugins

		//TypeCheck before functionCall memberFunctionInterface!!!

		//TODO: SMARTPOINTER!; PlayerManager;
		// pass Camera in evry draw function;
		// World::setActiveArea(const sf::IntRect& rectangle);
		// SaveFile class;
		// GameState in main();

		sf::ContextSettings contextSettings;
		contextSettings.antialiasingLevel = 8;

		sf::RenderWindow window( sf::VideoMode( 1080, 720 ), "TestWindow", sf::Style::Default, contextSettings );
		window.setVerticalSyncEnabled( true );

		kg::ResourceManagement resm;
		kg::PluginManagement pluginManagement( resm );
		kg::nMessageServer messageServer;

		std::vector<kg::NetworkInputHandler*> networkInputHandler;
		networkInputHandler.push_back( new StandartNetworkInputHandler );

		cClient client( window,
						pluginManagement,
						messageServer,
						networkInputHandler,
						nNetworkIdentification( sf::IpAddress::getLocalAddress(),
						nMessageServer::STANDART_MESSAGE_PORT ) );

		sServer server( true,
						pluginManagement,
						messageServer,
						networkInputHandler );

		sf::Event ev;

		while( window.isOpen() )
		{
			window.clear( sf::Color::Green );

			while( window.pollEvent( ev ) )
			{
				switch( ev.type )
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			messageServer.update();
			server.update();
			client.update();
			client.draw();

			window.display();
		}

		for( const auto& el : networkInputHandler )
			delete el;

		return 0;
	}
	catch( const std::exception& ex )
	{
		cout << ex.what() << endl;
		system( "pause" );
		return -999;
	}
};