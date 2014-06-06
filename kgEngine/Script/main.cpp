//_______MAIN_______//

//////////
// This file (main.cpp) is temporary.
// It is only used for unit testing
//////////

#pragma once
#include "stdafx.h"
#include "ksHelper.h"

#include "implementation/ksSubcode.h"
#include "implementation/ksDummy.h"
#include "implementation/ksReturnStatement.h"
#include "implementation/ksFunctionCall.h"
#include "implementation/ksGetFromStack.h"
#include "implementation/ksMemberOperator.h"
#include "implementation/ksString.h"

using namespace std;
using namespace kg;


int foo( std::string i )
{
	cout << "success" << i << endl;
	return 500;
}


int main()
{
	try
	{
		ksLibrary lib;
		ksRegisterStandartTypes( lib );
		lib.tokenConstructors[ksTOKEN_PRIORITY::SUBCODE].push_back( std::make_shared<ksSubcodeConstructor>() );
		lib.tokenConstructors[ksTOKEN_PRIORITY::FUNCTION_CALL].push_back( std::make_shared<ksFunctionCallConstructor>() );
		lib.tokenConstructors[ksTOKEN_PRIORITY::DUMMY].push_back( std::make_shared<ksDummyConstructor>() );
		lib.tokenConstructors[ksTOKEN_PRIORITY::RETURN_STATEMENT].push_back( std::make_shared<ksReturnStatementConstructor>() );
		lib.tokenConstructors[ksTOKEN_PRIORITY::GET_FROM_STACK].push_back( std::make_shared<ksGetFromStackConstructor>() );
		lib.tokenConstructors[ksTOKEN_PRIORITY::OPERATOR_MEMBER].push_back( std::make_shared<ksMemberOperatorConstructor>() );
		lib.tokenConstructors[ksTOKEN_PRIORITY::STRING].push_back( std::make_shared<ksStringConstructor>() );

		auto fooMaster = ksCreateFunctionMaster( "foo" );
		ksRegisterOverload( fooMaster, std::vector < std::string > {"string"}, &foo );
		lib.registerFunction( fooMaster );


		auto retVal = ksRunScript( lib, "testSkript.txt" );

		if( retVal != nullptr )
			cout << *retVal->getCppInstance<int>() << endl;
		else
			cout << "error" << endl;

		system( "pause" );
	}
	catch( std::exception& e )
	{
		cout << e.what() << endl;
	}


}