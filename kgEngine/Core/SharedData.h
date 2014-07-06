#pragma once

namespace kg
{
	const float pi = 3.14159265;

	//sent from client
	namespace MESSAGE_ID_CLIENT
	{
		enum
		{
			CHUNK_DATA_REQUEST,
			SET_TILE_REQUEST,
			CONNECTION_REQUEST,
			LAST_ELEMENT
		};
	}

	//sent from server
	namespace MESSAGE_ID_SERVER
	{
		enum
		{
			CHUNK_DATA_REQUEST_ANSWER = MESSAGE_ID_CLIENT::LAST_ELEMENT + 1,
			CONNECTION_REQUEST_ANSWER,
			LAST_ELEMENT
		};
	}

	namespace GAME_STATE_ID
	{
		enum
		{
			STANDART
		};
	}

	static const char standartSplitChar = ';';
	static const sf::Uint16 standartServerRecievePort = 42000;
	static const sf::Uint16 clientToServerPort = 42000;

	static const int chunkSizeInTiles = 20;
	static const int tileSizeInPixel = 64;

	//paths
	static const std::string resourceFolderPath = "Resource/";
	static const std::string fontFolderName = "Fonts/";
	static const std::string widgetFolderName = "TGUI/";

	static const std::string informationFileExtension = ".xml";
	static const std::string textureFileExtension = ".png";

	static const std::string tguiConfigBlack = "Black.conf";


	//GUI
	static const std::string editMenuName = "Edit";
	static const std::string editMenuTileItem = "TileDrawing";

	static const std::string createMenuName = "Database";
	static const std::string createMenuTileItem = "Add tile";

	static const std::string connectionMenuName = "Connection";
	static const std::string connectionMenuConnectItem = "Connect to Server";
}
