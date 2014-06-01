#include "ksHelper.h"

namespace kg
{

	void ksRegisterStandartTypes( ksLibrary& library )
	{
		auto mInt = ksCreateClassMaster<int>( "int" );
		library.registerType( mInt );

		auto mStr = ksCreateClassMaster<std::string>( "string" );
		library.registerType( mStr );

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
		library.rawTokens["!"] = ksRAW_TOKEN_ID::_EXCLAMATION_MARK;
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
		library.rawTokens["DUMMY"] = ksRAW_TOKEN_ID::_DUMMY;
	}

	std::shared_ptr<ksClassInstance> ksRunScript( ksLibrary& library, const std::string& path )
	{
		ksScript script( library );
		script.loadFromFile( path );
		return script.interpret();
	}

	std::shared_ptr<ksFunctionMaster> ksCreateFunctionMaster( const std::string& name )
	{
		return std::make_shared<ksFunctionMaster>( name );
	}

}