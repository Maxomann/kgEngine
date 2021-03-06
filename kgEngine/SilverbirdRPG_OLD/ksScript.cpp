#include "ksScript.h"

namespace kg
{

	ksScript::ksScript( ksLibrary& library )
		: r_library( library )
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
			std::swap( m_code, code );

			m_isInterpreted = false;
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
			m_isInterpreted = false;
			return true;
		}
		else
			return false;
	}

	bool ksScript::isLoaded() const
	{
		return m_code.size() != NULL;
	}

	std::shared_ptr<ksClassInstance> ksScript::interpret()
	{
		ksCode code( r_library.tokenConstructors,
					 r_library.rawTokens,
					 m_code
					 );
		m_isInterpreted = true;
		
		return code.execute( r_library, m_stack );

	}

	bool ksScript::isInterpreted() const
	{
		return m_isInterpreted;
	}

}