#include "ksScript.h"

using namespace kg;


kg::ksScript::ksScript( ksTokenConstructorMap& tokenConstructors,
						ksFunctionMap& availableFunctions,
						ksParentMap& availableCppObjectTypes )
						:r_availableFunctions( availableFunctions ),
						r_availableCppObjectTypes( availableCppObjectTypes ),
						r_tokenConstructors( tokenConstructors )
{

}

bool kg::ksScript::loadFromFile( const std::string& path )
{
	if( !isLoaded() )
	{
		//open file from path
		std::ifstream file;
		file.open( path );
		if( !file.is_open() )
			REPORT_ERROR( "opening the file failed" );

		//read file
		std::string code;
		std::string temp;
		while( std::getline( file, temp ) )
		{
			code += "\n";
			code += temp;
			temp.clear();
		}
		code += "\n";
		code += temp;
		file.close();

		//refresh internal code
		m_code = code;

		return true;
	}
	else
		return false;

}

bool kg::ksScript::loadFromString( const std::string& code )
{
	if( !isLoaded() )
	{
		m_code = code;
		return true;
	}
	else
		return false;
}

void kg::ksScript::interpret()
{

	ksCode code( r_tokenConstructors,
				 m_code );

	ksReferenceContainer refCon( r_availableFunctions,
								 r_availableCppObjectTypes,
								 m_stack );

	code.execute( refCon );
}

bool kg::ksScript::isLoaded()
{
	return m_code != "";
}



