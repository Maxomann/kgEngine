//_______CONNECT_______//

#pragma once
#include "stdafx.h"
#include "Client.h"
#include "MessageHandlers.h"

using namespace std;
using namespace kg;

extern "C" __declspec(dllexport) void kgConnect( pPluginManager& pluginManager )
{
	pluginManager.addExtensionProvider<cCore, Client>();

	pluginManager.addExtensionProvider<nNetworkManager, ChunkDataRequestAnswerHandler>();
}
