#pragma once
#include "AnimationSettings.h"

namespace kg
{
	struct TileSettings : public AnimationSettings
	{
		std::string tileName="-1";
		std::string tileTexturePath = "-1";

		virtual bool loadFromFile( const std::string& path )override;
		virtual bool saveToFile( const std::string path )const;


		const char* TILE_NAME = "tileName";
		const char* TILE_TEXTURE_PATH = "tileTexturePath";
	};
}
