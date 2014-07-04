//_______CONNECT_______//

#pragma once
#include "stdafx.h"
#include "Server.h"
#include "Network/MessageHandlers.h"

using namespace std;
using namespace kg;

extern "C" __declspec(dllexport) void kgConnect( pPluginManager& pluginManager )
{
	pluginManager.addExtensionProvider<cCore, Server>();

	//NetworkHandler
	pluginManager.addExtensionProvider<nNetworkManager, ChunkDataRequestHandler>();
	pluginManager.addExtensionProvider<nNetworkManager, SetTileRequestHandler>();
	pluginManager.addExtensionProvider<nNetworkManager, ConnectionRequestHandler>();
}
