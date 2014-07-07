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

		cCore application(pluginManager);
		pluginManager.fillExtandable<cCore>( application );
		application.initExtensions( pluginManager );

		application.networkManager.addConnection( sf::IpAddress::LocalHost, 42000, 42000 );

		application.setServerIp( sf::IpAddress::LocalHost );
		application.setServerPort( 42000 );

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
