#include "../ConfiguratedTexture.h"

namespace kg
{
	const char ConfiguratedTexture::FILE_EXTENSION[] = "tcnf";

	bool ConfiguratedTexture::loadFromFile( const std::string& path )
{
		if( !m_texture.loadFromFile( path ) )
			return false;

		//extract file extension from string and change it to .tcnf (Texture Config)
		std::string pathCopy( path );
		int pos = pathCopy.size() - 1;
		while( pathCopy.at( pos ) != '.' )
		{
			pathCopy.pop_back();
			pos--;
		}
		pathCopy += FILE_EXTENSION;
		m_config.loadFromFile( pathCopy );

		return true;
	}

	void ConfiguratedTexture::applyToSprite( sf::Sprite& sprite )
	{
		sprite.setTexture( m_texture );

		// scale the sprite like the file says
		sprite.setScale( sf::Vector2f( ( float )std::atoi( m_config.getData( "scaleToX" ).c_str()) / ( float )m_texture.getSize().x,//x
			( float )std::atoi( m_config.getData( "scaleToY" ).c_str() ) / ( float )m_texture.getSize().y ) );//y
	}

}
