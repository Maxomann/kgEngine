#pragma once

namespace kg
{
	//sent from client
	namespace MESSAGE_ID_CLIENT
	{
		enum
		{
			CHUNK_DATA_REQUEST,
			LAST_ELEMENT
		};
	}

	//sent from server
	namespace MESSAGE_ID_SERVER
	{
		enum
		{
			CHUNK_DATA_REQUEST_ANSWER = MESSAGE_ID_CLIENT::LAST_ELEMENT + 1,
			LAST_ELEMENT
		};
	}

	namespace GUI_STATE
	{
		enum
		{
			DEFAULT
		};
	}

	static const char standartSplitChar = ';';

	static const int chunkSizeInTiles = 20;
	static const int tileSizeInPixel = 50;

	static const sf::Uint16 clientToServerPort = 42000;

	static const std::string resourceFolderPath = "Resource/";
	static const std::string fontFolderName = "Fonts/";
}
