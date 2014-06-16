//_______CONFIGURATED_TEXTURE_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class ConfiguratedTexture
	{
		sf::Texture m_texture;
		aDataByIdentifierFile m_config;

	public:
		// loads configuration data from TextureName.tcnf (Texture Config)
		// scaleToX: xxx = final size X without zoom in pixel
		// scaleToY: xxx = final size Y without zoom in pixel
		bool loadFromFile( const std::string& path );

		void applyToSprite( sf::Sprite& sprite );

		//"tcnf"
		static const char FILE_EXTENSION[];
	};
}
