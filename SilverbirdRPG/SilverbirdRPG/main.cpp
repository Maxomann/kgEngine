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
#include "ksCode.h"
#include "ksBrackets.h"
#include "ksFunctionCall.h"
#include "ksIdentifier.h"
#include "ksScript.h"

using namespace std;
using namespace kg;

std::shared_ptr<ksObject> func( const ksObjectVector& vec )
{
	cout << "FunctionCall Success" << endl;
	return nullptr;
}

int main()
{

	ksTokenConstructorMap tokenConstructors;
	tokenConstructors[token::BracketOpenConstructor::PRIORITY]
		.push_back( std::make_shared<token::BracketOpenConstructor>() );
	tokenConstructors[token::BracketCloseConstructor::PRIORITY]
		.push_back( std::make_shared<token::BracketCloseConstructor>() );
	tokenConstructors[token::FunctionCallConstructor::PRIORITY]
		.push_back( std::make_shared<token::FunctionCallConstructor>() );
	tokenConstructors[token::IdentifierConstructor::PRIORITY]
		.push_back( std::make_shared<token::IdentifierConstructor>() );

	ksParentMap availableCppObjectTypes;
	ksFunctionMap availableFunctions;
	availableFunctions["TestFunc"] = func;

	ksScript script(tokenConstructors, availableFunctions, availableCppObjectTypes);
	script.loadFromFile( "testSkript.txt" );
	script.interpret();

	system( "pause" );


	//Plugins

	//Subcode mit hilfe von Tokens realisieren

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
};