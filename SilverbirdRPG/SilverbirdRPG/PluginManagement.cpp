//_______PLUGIN_MANAGEMENT_H_______//
#pragma once
#include"PluginManagement.h"

namespace kg
{
	PluginManagement::PluginManagement( ResourceManagement& resourceManagement )
		: r_resourceManagement( &resourceManagement )
	{
		//////RESOURCEN LADEN//////

		DIR *cDir = opendir( ResourceManagement::PLUGIN_FOLDER_CLIENT );
		dirent *ent;

		//error melden wenn dir nicht geöffnet werden kann
		if( cDir == NULL )
		{
			closedir( cDir );
			throw(std::string( "PluginManagement::PluginManagement could not open client plugin dir." ));
		}

		while( (ent = readdir( cDir )) != NULL )
		{
			//wenn datei
			if( ent->d_type / DIRENT_CONST == 2 )
			{
				//Dateiendung abspalten
				auto vec = aSplitString::function( ent->d_name, '.', aSplitString::operation::ADD_NEXTWORD );
				//Für alle dateien mit Endung
				if( vec.size() > 1 )
				{
					//Wenn FieldFactoryFile
					if( vec.at( 1 ) == cFieldFactory::FILE_EXTENSION )
					{
						cFieldFactory fac( ResourceManagement::PLUGIN_FOLDER_CLIENT + std::string( ent->d_name ), *r_resourceManagement );

						m_cFieldFactorys.insert( std::make_pair( fac.getId(), fac ) );
					}
				}
			}
		}
		closedir( cDir );

		//////BIGGEST_TILE_SIZE BESTIMMEN//////
		for( auto& el : m_cFieldFactorys )
		{
			if( el.second.getSizeInPixel() > m_biggestTileSize )
				m_biggestTileSize = el.second.getSizeInPixel();
		}

		//////BIGGEST_TILE_SIZE ANWENDEN//////
		for( auto& el : m_cFieldFactorys )
		{
			el.second.setFinalSizeInPixel( m_biggestTileSize );
		}
	}
	cField* PluginManagement::getClientField( const int id, const sf::Vector2i& positionInTiles )
	{
		auto it = m_cFieldFactorys.find( id );

		if( it == m_cFieldFactorys.end() )
			return nullptr;//Wenn entsprefchende fieldFactory nicht geladen, return nullptr
		else
			return it->second.getField( positionInTiles );
	}
	int PluginManagement::getSizeOfTile()const
	{
		return m_biggestTileSize;
	}
}