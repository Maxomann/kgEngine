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

		auto nameNode = doc.first_node( "tileName" );
		if( !nameNode )
			REPORT_ERROR_FILEACCESS( "tileName node not found in file" + path );
		tileName = nameNode->value();

		auto textureNode = doc.first_node( "tileTexturePath" );
		if( !textureNode )
			REPORT_ERROR_FILEACCESS( "tileTexturePath node not found in file" + path );
		tileTexturePath = textureNode->value();

		delete[] file;
		return true;
	}

}
