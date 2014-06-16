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

	static const char standartSplitChar = ';';

	static const sf::Vector2i chunkSize = { 19, 19 };

	static const std::string resourceFolderPath = "Resource/";
}
