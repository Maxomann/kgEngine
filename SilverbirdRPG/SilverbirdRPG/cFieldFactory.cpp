//_______FIELD_FACTORY_CPP_______//
#pragma once
#include "cFieldFactory.h"

namespace kg
{
	const std::string cFieldFactory::FILE_EXTENSION = std::string( ".cField" );

	cFieldFactory::cFieldFactory( const std::string& path, ResourceManagement& resourceManagement )
		:Factory<cField>( resourceManagement )
	{
			m_loadFromFile( path );
	}
	cField* cFieldFactory::getField( const sf::Vector2i& postionInTiles )
	{
		return new cField(
			*(r_resourceManagement->getResourceFromResourceFolder<sf::Texture>( m_pathOfTexture )),
			m_positionOnTexture,
			m_sizeInPixel,
			m_finalSizeInPixel,
			postionInTiles,
			this );
	}
	void cFieldFactory::setFinalSizeInPixel( const int size )
	{
		m_finalSizeInPixel = size;
	}
	int cFieldFactory::getSizeInPixel()const
	{
		return m_sizeInPixel;
	}
	std::string	cFieldFactory::getName()const
	{
		return m_name;
	}
	void cFieldFactory::m_loadFromFile( const std::string& path )
	{
		std::ifstream file;
		file.open( path );
		//File not open
		if( !file.is_open() )
			throw std::exception( ("FieldFactory::m_loadFromFile Could not open file: " + path).c_str() );

		//Lesen
		std::string line;

		getline( file, line );
		//Id
		m_id = std::atoi( line.c_str() );

		getline( file, line );
		//Name
		m_name = line;

		getline( file, line );
		//PathOfTexture
		m_pathOfTexture = line;

		//PositionOnTexture holen und trennen
		getline( file, line );
		auto vec = aSplitString::function( line, ' ', ',',
										   aSplitString::operation::REMOVE );
		//PositionOnTexture.x
		m_positionOnTexture.x = atoi( vec.at( 0 ).c_str() );
		//PositionOnTexture.y
		m_positionOnTexture.y = atoi( vec.at( 1 ).c_str() );

		getline( file, line );
		m_sizeInPixel = atoi( line.c_str() );

		return;
	}
}