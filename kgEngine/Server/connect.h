//_______CONNECT_______//

#pragma once
#include "stdafx.h"
#include "Server.h"

using namespace std;
using namespace kg;

extern "C" __declspec(dllexport) void kgConnect( pPluginManager& pluginManager )
{
	pluginManager.addExtensionProvider<cCore, Server>();
}