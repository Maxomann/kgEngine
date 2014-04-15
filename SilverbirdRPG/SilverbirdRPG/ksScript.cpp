#include "ksScript.h"

namespace kg
{

	ksScript::ksScript( ksLibrary& library,
						const ksTokenConstructorPriorityMap& tokenConstructors,
						const ksRawTokenMap& rawTokens )
						: r_tokenConstructors( tokenConstructors ),
						r_rawTokens( rawTokens ),
						r_library(library)
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

	void ksScript::interpret()
	{
		ksCode code(r_tokenConstructors,
					 r_rawTokens,
					 m_code
					 );
		code.execute( r_library, m_stack );

		m_isInterpreted = true;
	}

	bool ksScript::isInterpreted() const
	{
		return m_isInterpreted;
	}

}