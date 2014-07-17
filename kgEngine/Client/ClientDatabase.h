//_______DATABASE_______//

#pragma once
#include "stdafx.h"
#include "Settings/TileSettings.h"

namespace kg
{
	class ClientDatabase : public pExtension
	{
		aDataByIdentifierFile* m_tileList;
		std::map< int, TileSettings > m_tiles;
		std::map< int, sf::Texture > m_tileTextures;

		aDataByIdentifierFile* m_configFile;

	public:
		//also reload
		void loadAllResources( cCore& core );
		//also reload
		void saveAllResources();

		//Tiles
		void loadTiles( cCore& core );
		void saveTiles();
		const std::string& getTileName( int tileID )const;
		int getTileID( const std::string& name )const;
		const TileSettings& getTile( int tileID )const;
		const std::map<int, TileSettings>& getTiles()const;
		sf::Texture& getTileTexture( int tileID );
		const std::map<int, sf::Texture>& getTileTextures();

		void setTile( int tileID, const TileSettings& settings );
		void setFirstFreeTileID( const TileSettings& settings );
		void moveTileID( int from, int to );

		//ConfigFile
		void loadConfigFile( cCore& core );
		void saveConfigFile();
		const std::string& getWindowName()const;
		const int getAntialiasingLevel()const;
		const sf::Vector2i getWindowResolution()const;
		bool isVsynchEnabled()const;
		const sf::Vector2i getRenderDistance()const;//TODO

		void setWindowName( const std::string& name );
		void setAntialiasingLevel( int level );
		void setWindowResolution( const sf::Vector2i windowResolution );
		void setVsynchEnabled( bool enable );
		void setRenderDistance( const sf::Vector2i renderDistance );

		//pExtension
		virtual std::string info() const;
	};
}
