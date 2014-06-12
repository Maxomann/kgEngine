//_______MAIN_______//

#pragma once
#include <Network/nNetworkManger.h>
#include <Plugin/pPluginManager.h>
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
	pPluginManager pluginManager;
	//pluginManager.loadPluginsFromFile( "client.dll" );
	//pluginManager.loadPluginsFromFile( "server.dll" );

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

	return 0;
}
