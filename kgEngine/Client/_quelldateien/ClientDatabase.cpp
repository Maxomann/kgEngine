#include "../ClientDatabase.h"

namespace kg
{


	void ClientDatabase::loadAllResources( cCore& core )
	{
		loadTiles( core );
		loadConfigFile( core );
	}

	void ClientDatabase::saveAllResources()
	{
		saveTiles();
		saveConfigFile();
	}

	void ClientDatabase::loadTiles( cCore& core )
	{
		m_tileList = &core.resourceManagement.getResourceFromResourceFolder<aDataByIdentifierFile>( TileListName + configFileExtension );

		for( const auto& el : m_tileList->getAllData() )
		{
			int id = std::atoi( el.first.c_str() );
			const std::string& tileConfigFilePath = el.second;

			auto& tileSettings = core.resourceManagement.reloadResourceFromResourceFolder<TileSettings>( tileConfigFilePath );
			m_tiles[id] = tileSettings;
			m_tileTextures[id] = core.resourceManagement.reloadResourceFromResourceFolder<sf::Texture>( tileSettings.tileTexturePath );
		}
	}

	void ClientDatabase::saveTiles()
	{
		for( const auto& el : m_tileList->getAllData() )
		{
			int id = std::atoi( el.first.c_str() );
			const std::string& tileConfigFilePath = el.second;

			m_tiles.at( id ).saveToFile( resourceFolderPath + tileConfigFilePath );
		}
		m_tileList->saveToFile( resourceFolderPath+TileListName + configFileExtension );
	}

	const std::string& ClientDatabase::getTileName( int tileID ) const
	{
		return m_tiles.at( tileID ).tileName;
	}

	int ClientDatabase::getTileID( const std::string& name ) const
	{
		for( const auto& el : m_tiles )
			if( el.second.tileName == name )
				return el.first;
		REPORT_ERROR_DATABASE( "requested tile not loaded" );
	}

	const TileSettings& ClientDatabase::getTile( int tileID ) const
	{
		return m_tiles.at( tileID );
	}

	const std::map<int, TileSettings>& ClientDatabase::getTiles() const
	{
		return m_tiles;
	}

	sf::Texture& ClientDatabase::getTileTexture( int tileID )
	{
		return m_tileTextures.at( tileID );
	}

	const std::map<int, sf::Texture>& ClientDatabase::getTileTextures()
	{
		return m_tileTextures;
	}

	void ClientDatabase::setTile( int tileID, const TileSettings& settings )
	{
		m_tiles[tileID] = settings;
	}

	void ClientDatabase::setFirstFreeTileID( const TileSettings& settings )
	{
		auto it = begin( m_tiles );
		for( const auto& el : m_tiles )
			++it;
		m_tiles[it->first + 1] = settings;
	}

	void ClientDatabase::loadConfigFile( cCore& core )
	{
		m_configFile = &core.resourceManagement.reloadResource<aDataByIdentifierFile>( clientConfigFileName+configFileExtension );
	}

	void ClientDatabase::saveConfigFile()
	{
		m_configFile->saveToFile( resourceFolderPath + clientConfigFileName + configFileExtension );
	}

	const std::string& ClientDatabase::getWindowName() const
	{
		return m_configFile->getData( "window_name" );
	}

	const int ClientDatabase::getAntialiasingLevel() const
	{
		return atoi( m_configFile->getData( "antialiasing" ).c_str() );
	}

	const sf::Vector2i ClientDatabase::getWindowResolution() const
	{
		return{ std::atoi( m_configFile->getData( "resx" ).c_str() ),
			std::atoi( m_configFile->getData( "resy" ).c_str() ) };
	}

	bool ClientDatabase::isVsynchEnabled() const
	{
		if( m_configFile->getData( "vsynch" ) == "true" )
			return true;
		else
			return false;
	}

	const sf::Vector2i ClientDatabase::getRenderDistance() const
	{
		sf::Vector2i renderDistance;
		renderDistance.x = atoi( m_configFile->getData( "renderDistanceX" ).c_str() );
		renderDistance.y = atoi( m_configFile->getData( "renderDistanceY" ).c_str() );
		return renderDistance;
	}

	void ClientDatabase::setWindowName( const std::string& name )
	{
		m_configFile->setData( "windowName", name );
	}

	void ClientDatabase::setAntialiasingLevel( int level )
	{
		m_configFile->setData( "antialiasing", std::to_string( level ) );
	}

	void ClientDatabase::setWindowResolution( const sf::Vector2i windowResolution )
	{
		m_configFile->setData( "resX", std::to_string( windowResolution.x ) );
		m_configFile->setData( "resY", std::to_string( windowResolution.y ) );
	}

	void ClientDatabase::setVsynchEnabled( bool enable )
	{
		if( enable )
			m_configFile->setData( "vsynch", "true" );
		else
			m_configFile->setData( "vsynch", "false" );
	}

	void ClientDatabase::setRenderDistance( const sf::Vector2i renderDistance )
	{
		m_configFile->setData( "renderDistanceX", std::to_string( renderDistance.x ) );
		m_configFile->setData( "renderDistanceY", std::to_string( renderDistance.y ) );
	}

	void ClientDatabase::moveTileID( int from, int to )
	{
		auto tempFrom = m_tiles[from];
		auto tempTo = m_tiles[to];

		m_tiles[from] = tempTo;
		m_tiles[to] = tempFrom;

		return;
	}

	std::string ClientDatabase::info() const
	{
		return "DATABASE-Client";
	}

}
