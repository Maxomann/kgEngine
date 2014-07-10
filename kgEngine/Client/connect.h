//_______CONNECT_______//

#pragma once
#include "stdafx.h"
#include "Client.h"
#include "Network/MessageHandlers.h"
#include "ClientDatabase.h"
#include "GameState/Editor/EditorGuiPlugins.h"

using namespace std;
using namespace kg;

extern "C" __declspec(dllexport) void kgConnect( pPluginManager& pluginManager )
{
	pluginManager.addExtensionProvider<cCore, Client>();
	pluginManager.addExtensionProvider<cCore, ClientDatabase>();

	//NetworkHandler
	pluginManager.addExtensionProvider<nNetworkManager, ChunkDataRequestAnswerHandler>();
	pluginManager.addExtensionProvider<nNetworkManager, ConnectionRequestAnswerHandler>();

	//GameStates
	pluginManager.addExtensionProvider<Client, TestGameState>();


	//GUI
	pluginManager.addExtensionProvider<TileDrawingWindow,
		pGenericProvider<PointBrushSubWindow, TileDrawingSubWindow>>();
}
