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
#include "ksLibrary.h"

using namespace std;
using namespace kg;


class Foo
{
public:
	int someFunction( int i )const
	{
		cout << "Foo!" << endl;
		cout << i << endl;
		return i+1;
	}
};

std::string bar( const std::string& i )
{
	cout << "Foo!" << endl;
	cout << i << endl;
	return i + "XxX";
}

int main()
{
	try
	{
		ksLibrary lib;
		lib.registerType<int>( ksCreateClassMaster<int>( "int" ) );

		auto fooMaster=ksCreateClassMaster<Foo>( "Foo" );
		ksRegisterMemberFunction( fooMaster, "someFunction", { "int" }, &Foo::someFunction );

		lib.registerType<Foo>( fooMaster );

		auto fooInst = lib.getType<Foo>()->createNewInstance();
		fooInst->callMemberFunction( "someFunction", { "int" }, { lib.getType<int>()->createInstance( new int( 33 ) ) } );

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