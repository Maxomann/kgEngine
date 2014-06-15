//_______CONNECT_______//

#pragma once
#include "stdafx.h"
#include "Server.h"
#include "MessageHandlers.h"

using namespace std;
using namespace kg;

extern "C" __declspec(dllexport) void kgConnect( pPluginManager& pluginManager )
{
	pluginManager.addExtensionProvider<cCore, Server>();

	pluginManager.addExtensionProvider<nNetworkManager, ChunkDataRequestHandler>();
}