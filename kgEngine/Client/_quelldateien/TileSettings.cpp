#include "../Settings/TileSettings.h"

using namespace rapidxml;

namespace kg
{
	bool TileSettings::loadFromFile( const std::string& path )
	{
		AnimationSettings::loadFromFile( path );

		auto str = aLoadFileToString( path );

		char* file = new char[str.length() + 1];
		strcpy( file, str.c_str() );

		xml_document<> doc;
		doc.parse<0>( file );

		auto nameNode = doc.first_node( TILE_NAME );
		if( !nameNode )
			REPORT_ERROR_FILEACCESS( TILE_NAME+ " node not found in file" + path );
		tileName = nameNode->value();

		auto textureNode = doc.first_node( TILE_TEXTURE_PATH );
		if( !textureNode )
			REPORT_ERROR_FILEACCESS( TILE_TEXTURE_PATH+" node not found in file" + path );
		tileTexturePath = textureNode->value();

		delete[] file;

		if( tileName == "-1" || tileTexturePath == "-1"||
			tileName == "" || tileTexturePath == "" )
			return false;
		return true;
	}

	bool TileSettings::saveToFile( const std::string path )const
	{
		AnimationSettings::saveToFile( path );

		auto file = aLoadFileToCharPointer( path );

		xml_document<> doc;
		doc.parse<0>( file );
		

		doc.append_node( doc.allocate_node( node_element, TILE_NAME, tileName.c_str() ) );
		doc.append_node( doc.allocate_node( node_element, TILE_TEXTURE_PATH, tileTexturePath.c_str() ) );

		std::stringstream s;
		s << doc;
		aSaveStringToFile( path, s.str() );

		delete[] file;

		return true;
	}

}
