//_______MAIN_______//

#pragma once
#include <pPluginManager.h>
#include "cCore.h"

using namespace std;
using namespace kg;

int main()
{
	pPluginManager pluginManager;
	//pluginManager.loadPlugins(  );

	cCore application;
	pluginManager.fillExtandable<cCore>( application );
	pluginManager.addExtensionProvider<cCore, int>();

	//Main loop
	while( !application.shouldClose() )
	{
		application.frame();
	}

	return 0;
}