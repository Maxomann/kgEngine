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

	void ksScript::interpret()
	{
		ksCode code( r_library.tokenConstructors,
					 r_library.rawTokens,
					 m_code
					 );
		code.execute( r_library, m_stack );

		m_isInterpreted = true;
	}

	bool ksScript::isInterpreted() const
	{
		return m_isInterpreted;
	}

	void ksRegisterStandartTypes( ksLibrary& library )
	{

	}

	void ksRunScript( ksLibrary& library, const std::string& path )
	{
		ksScript script( library );
		script.loadFromFile( path );
		script.interpret();
	}

	std::shared_ptr<ksFunctionMaster> ksCreateFunctionMaster( const std::string& name )
	{
		return std::make_shared<ksFunctionMaster>( name );
	}

}