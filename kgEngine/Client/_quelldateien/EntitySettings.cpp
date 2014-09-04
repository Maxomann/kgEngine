#include "../Settings/EntitySettings.h"

using namespace rapidxml;

namespace kg
{

	bool EntitySettings::loadFromFile( const std::string& path )
	{
		entityName = "-1";
		entityTexturePath = "-1";

		AnimationSettings::loadFromFile( path );

		auto str = aLoadFileToString( path );

		char* file = new char[str.length() + 1];
		strcpy( file, str.c_str() );

		xml_document<> doc;
		doc.parse<0>( file );

		auto nameNode = doc.first_node( ENTITY_NAME );
		if( !nameNode )
			REPORT_ERROR_FILEACCESS( ENTITY_NAME + " node not found in file" + path );
		entityName = nameNode->value();

		auto textureNode = doc.first_node( ENTITY_TEXTURE_PATH );
		if( !textureNode )
			REPORT_ERROR_FILEACCESS( ENTITY_TEXTURE_PATH + " node not found in file" + path );
		entityTexturePath = textureNode->value();

		delete[] file;

		if( entityName == "-1" || entityTexturePath == "-1" ||
			entityName == "" || entityTexturePath == "" )
			return false;
		return true;
	}

	bool EntitySettings::saveToFile( const std::string path )const
	{
		AnimationSettings::saveToFile( path );

		auto file = aLoadFileToCharPointer( path );

		xml_document<> doc;
		doc.parse<0>( file );

		doc.append_node( doc.allocate_node( node_element, ENTITY_NAME, entityName.c_str() ) );
		doc.append_node( doc.allocate_node( node_element, ENTITY_TEXTURE_PATH, entityTexturePath.c_str() ) );

		std::stringstream s;
		s << doc;
		aSaveStringToFile( path, s.str() );

		delete[] file;

		return true;
	}
}
