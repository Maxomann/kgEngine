//_______DATABASE_______//

#pragma once
#include "stdafx.h"
#include "Settings/TileSettings.h"

namespace kg
{
	class ClientDatabase : public pExtension, public aCallbackSender<ClientDatabase>
	{
		aDataByIdentifierFile*        m_tileList;
		std::map< int, TileSettings > m_tiles;
		std::map< int, sf::Texture >  m_tileTextures;

		aDataByIdentifierFile*        m_configFile;

	public:
		//also reload
		void         loadAllResources( cCore& core );
		//also       reload
		void         saveAllResources();

		//Tiles
		void         loadTiles( cCore& core );
		void         saveTiles();
		void         tilesModified();
		const        std::string& getTileName( int tileID )const;
		int          getTileID( const std::string& name )const;
		const        TileSettings& getTile( int tileID )const;
		const        std::map<int, TileSettings>& getTiles()const;
		sf::Texture& getTileTexture( int tileID );
		const        std::map<int, sf::Texture>& getTileTextures();
		//returns    true if tileSettings and tileTexture are available
		//returns    false otherwise
		bool         isTileAvailable( int tileID )const;

		void         setTile( int tileID, const TileSettings& settings );
		int          setFirstFreeTileID( const TileSettings& settings );
		void         moveTileID( int from, int to );

		//ConfigFile
		void         loadConfigFile( cCore& core );
		void         saveConfigFile();
		void         configFileModified();
		const        std::string& getWindowName()const;
		const        int getAntialiasingLevel()const;
		const        sf::Vector2i getWindowResolution()const;
		bool         isVsynchEnabled()const;
		const        sf::Vector2i getRenderDistance()const;
		bool		 isFullscreenEnabled()const;

		void         setWindowName( const std::string& name );
		void         setAntialiasingLevel( int level );
		void         setWindowResolution( const sf::Vector2i windowResolution );
		void         setVsynchEnabled( bool enable );
		void         setRenderDistance( const sf::Vector2i renderDistance );
		void		 setFullscreenEnabled( bool enable );

		//pExtension
		virtual      std::string info() const;
	};
}
