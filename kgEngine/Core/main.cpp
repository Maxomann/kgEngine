//_______MAIN_______//

#pragma once
#include <pPluginManager.h>
#include <iostream>
#include "cCore.h"
#include "cCoreExtension.h"

using namespace std;
using namespace kg;


int main()
{
	pPluginManager pluginManager;
	//pluginManager.loadPlugins(  );

	cCore application;
	pluginManager.fillExtandable<cCore>( application );


	//Main loop
	while( !application.shouldClose() )
	{
		application.frame();
	}

	return 0;
}