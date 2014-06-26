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

		std::string scaleXY = m_config.getData( "scaleToXY" );

		//scale on X&Y is the same
		if( scaleXY != "" )
		{
			int scaleToXY = atoi( scaleXY.c_str() );

			if( scaleToXY == 0 )
			{
				//No need to scale sprite here
			}
			else
			{
				// scale the sprite like the file says
				sprite.setScale(
					sf::Vector2f( scaleToXY / ( float )m_texture.getSize().x,//x
					scaleToXY / ( float )m_texture.getSize().y )
					);//y
			}
		}
		//scale on X&Y not the same
		else
		{
			sf::Vector2i scaleTo( std::atoi( m_config.getData( "scaleToX" ).c_str() ),//x
								  std::atoi( m_config.getData( "scaleToY" ).c_str() ) );//y

			if( scaleTo.x == 0 )
			{
				if( scaleTo.y == 0 )
				{
					//No need to scale sprite here
				}
				else
				{
					// scale the sprite like the file says
					sprite.setScale(
						sf::Vector2f( 1.0f,//x
						scaleTo.y / ( float )m_texture.getSize().y )//y
						);
				}
			}
			else if( scaleTo.y == 0 )
			{
				// scale the sprite like the file says
				sprite.setScale(
					sf::Vector2f( scaleTo.x / ( float )m_texture.getSize().x,//x
					1.0f//y
					) );
			}
			else
			{
				// scale the sprite like the file says
				sprite.setScale(
					sf::Vector2f( scaleTo.x / ( float )m_texture.getSize().x,//x
					scaleTo.y / ( float )m_texture.getSize().y )
					);//y
			}
		}
	}
}