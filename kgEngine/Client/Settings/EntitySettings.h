//_______ENTITY_SETTINGS_______//

#pragma once
#include "AnimationSettings.h"

namespace kg
{
	class EntitySettings : public AnimationSettings
	{
		std::string entityName = "-1";
		std::string entityTexturePath = "-1";

		virtual bool loadFromFile( const std::string& path )override;
		virtual bool saveToFile( const std::string path )const;

		const char* ENTITY_NAME = "entityName";
		const char* ENTITY_TEXTURE_PATH = "entityTexturePath";
	};
}
