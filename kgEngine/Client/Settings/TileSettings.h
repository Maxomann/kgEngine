#pragma once
#include "AnimationSettings.h"

namespace kg
{
	struct TileSettings : public AnimationSettings
	{
		std::string tileName;

		virtual bool loadFromFile( const std::string& path )override;
	};
}
