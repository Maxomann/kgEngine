//_______MAIN_______//

#pragma once
#include "stdafx.h"
#include <iostream>
#include "cCore.h"
#include "cCoreExtension.h"

// Interface classes:
// pCoreExtension
// nMessage
// nMessageHandler

using namespace std;
using namespace kg;


int main()
{
	try
	{
		pPluginManager pluginManager;
		pluginManager.loadPluginsFromFile( "Client.dll" );
		pluginManager.loadPluginsFromFile( "Server.dll" );

		cCore application;
		pluginManager.fillExtandable<cCore>( application );

		pluginManager.fillExtandable<nNetworkManager>( application.networkManager );
		application.networkManager.initMessageHandlers();

		application.networkManager.addConnection( sf::IpAddress::getLocalAddress(), 42000 );

		//Main loop
		while( !application.shouldClose() )
		{
			application.frame();
		}
	}
	catch( std::exception& e )
	{
		cout << e.what() << endl;
		system( "pause" );
	}

	return 0;
}
