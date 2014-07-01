//_______CONNECT_______//

#pragma once
#include "stdafx.h"
#include "Client.h"
#include "Network/MessageHandlers.h"

using namespace std;
using namespace kg;

extern "C" __declspec(dllexport) void kgConnect( pPluginManager& pluginManager )
{
	pluginManager.addExtensionProvider<cCore, Client>();

	//NetworkHandler
	pluginManager.addExtensionProvider<nNetworkManager, ChunkDataRequestAnswerHandler>();

	//GameStates
	pluginManager.addExtensionProvider<Client, TestGameState>();

}
