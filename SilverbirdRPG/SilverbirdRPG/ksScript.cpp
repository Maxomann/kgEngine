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
		library.rawTokens["("] = ksRAW_TOKEN_ID::_FUNCTION_BEGIN;
		library.rawTokens[")"] = ksRAW_TOKEN_ID::_FUNCTION_END;
		library.rawTokens[";"] = ksRAW_TOKEN_ID::_EXPRESSION_END;
		library.rawTokens[","] = ksRAW_TOKEN_ID::_KOMMA;
		library.rawTokens["{"] = ksRAW_TOKEN_ID::_OBJECT_BEGIN;
		library.rawTokens["}"] = ksRAW_TOKEN_ID::_OBJECT_END;
		library.rawTokens["const"] = ksRAW_TOKEN_ID::_QUALIFIER;
		library.rawTokens["."] = ksRAW_TOKEN_ID::_DOT;
		library.rawTokens["\""] = ksRAW_TOKEN_ID::_STRING;
		library.rawTokens["="] = ksRAW_TOKEN_ID::_EQUAL;
		library.rawTokens["!"] = ksRAW_TOKEN_ID::_BANG;
		library.rawTokens["+"] = ksRAW_TOKEN_ID::_ADD;
		library.rawTokens["-"] = ksRAW_TOKEN_ID::_SUBTRACT;
		library.rawTokens["*"] = ksRAW_TOKEN_ID::_MULTIPLY;
		library.rawTokens["/"] = ksRAW_TOKEN_ID::_DIVIDE;
		library.rawTokens[">"] = ksRAW_TOKEN_ID::_BIGGER;
		library.rawTokens["<"] = ksRAW_TOKEN_ID::_SMALLER;
		library.rawTokens["function"] = ksRAW_TOKEN_ID::_FUNCTION;
		library.rawTokens["callback"] = ksRAW_TOKEN_ID::_CALLBACK;
		library.rawTokens["if"] = ksRAW_TOKEN_ID::_IF;
		library.rawTokens["while"] = ksRAW_TOKEN_ID::_WHILE;
		library.rawTokens["for"] = ksRAW_TOKEN_ID::_FOR;
		library.rawTokens["new"] = ksRAW_TOKEN_ID::_NEW;
		library.rawTokens["return"] = ksRAW_TOKEN_ID::_RETURN;
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