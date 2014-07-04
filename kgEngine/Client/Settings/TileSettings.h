#pragma once
#include "AnimationSettings.h"

namespace kg
{
	struct TileSettings : public AnimationSettings
	{
		std::string tileName;
		std::string tileTexturePath;

		virtual bool loadFromFile( const std::string& path )override;
	};
}
