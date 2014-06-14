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

		nNetworkManager networkManger;
		pluginManager.fillExtandable<nNetworkManager>( networkManger );
		networkManger.initMessageHandlers();

		cCore application;
		pluginManager.fillExtandable<cCore>( application );

		//Main loop
		while( !application.shouldClose() )
		{
			networkManger.frame( application );
			application.frame( networkManger );
		}
	}
	catch( std::exception& e )
	{
		cout << e.what() << endl;
		system( "pause" );
	}

	//to prevent mutex error
	std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	return 0;
}
