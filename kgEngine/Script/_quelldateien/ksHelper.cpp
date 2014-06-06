#include "../ksHelper.h"

namespace kg
{

	void ksRegisterStandartTypes( ksLibrary& library )
	{
		auto mInt = ksCreateClassMaster<int>( "int" );
		library.registerType( mInt );

		auto mStr = ksCreateClassMaster<std::string>( "string" );
		library.registerType( mStr );

		library.rawTokens["("] = ksRAW_TOKEN_ID::FUNCTION_BEGIN;
		library.rawTokens[")"] = ksRAW_TOKEN_ID::FUNCTION_END;
		library.rawTokens[";"] = ksRAW_TOKEN_ID::EXPRESSION_END;
		library.rawTokens[","] = ksRAW_TOKEN_ID::KOMMA;
		library.rawTokens["{"] = ksRAW_TOKEN_ID::OBJECT_BEGIN;
		library.rawTokens["}"] = ksRAW_TOKEN_ID::OBJECT_END;
		library.rawTokens["const"] = ksRAW_TOKEN_ID::QUALIFIER;
		library.rawTokens["."] = ksRAW_TOKEN_ID::DOT;
		library.rawTokens["\""] = ksRAW_TOKEN_ID::STRING;
		library.rawTokens["="] = ksRAW_TOKEN_ID::EQUAL;
		library.rawTokens["!"] = ksRAW_TOKEN_ID::EXCLAMATION_MARK;
		library.rawTokens["+"] = ksRAW_TOKEN_ID::ADD;
		library.rawTokens["-"] = ksRAW_TOKEN_ID::SUBTRACT;
		library.rawTokens["*"] = ksRAW_TOKEN_ID::MULTIPLY;
		library.rawTokens["/"] = ksRAW_TOKEN_ID::DIVIDE;
		library.rawTokens[">"] = ksRAW_TOKEN_ID::BIGGER;
		library.rawTokens["<"] = ksRAW_TOKEN_ID::SMALLER;
		library.rawTokens["function"] = ksRAW_TOKEN_ID::FUNCTION;
		library.rawTokens["callback"] = ksRAW_TOKEN_ID::FUNCTION_CALLBACK;
		library.rawTokens["if"] = ksRAW_TOKEN_ID::IF;
		library.rawTokens["while"] = ksRAW_TOKEN_ID::WHILE;
		library.rawTokens["for"] = ksRAW_TOKEN_ID::FOR;
		library.rawTokens["new"] = ksRAW_TOKEN_ID::NEW;
		library.rawTokens["return"] = ksRAW_TOKEN_ID::RETURN;
		library.rawTokens["DUMMY"] = ksRAW_TOKEN_ID::DUMMY;
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