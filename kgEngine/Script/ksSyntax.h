//_______CONTAINER_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class ksCode;
	class ksToken;
	class ksTokenConstructor;
	class ksClassInstance;
	class ksLibrary;
	class ksFunctionMaster;

	// first: token
	// second: tokenId
	typedef std::map<std::string, int> ksRawTokenMap;

	typedef std::vector<std::shared_ptr<ksCode>> ksCodeVector;

	typedef std::vector<const std::pair<std::string, int>> ksSplitCodeVector;

	// first: first line the token takes care of
	// second: token
	typedef std::map<int, std::shared_ptr<ksToken>> ksTokenMap;

	// first: priority
	// second: tokenConstructors with that priority
	typedef std::map<int, std::vector<std::shared_ptr<ksTokenConstructor>>> ksTokenConstructorPriorityMap;

	namespace ksRAW_TOKEN_ID
	{
		enum
		{
			FUNCTION_BEGIN,		// (
			FUNCTION_END,		// )
			EXPRESSION_END,		// ;
			KOMMA,				// ,
			OBJECT_BEGIN,		// {
			OBJECT_END,			// }
			QUALIFIER,			// const
			DOT,				// .
			STRING,				// "
			EQUAL,				// =
			EXCLAMATION_MARK,	// !
			ADD,				// +
			SUBTRACT,			// -
			MULTIPLY,			// *
			DIVIDE,				// /
			BIGGER,				// >
			SMALLER,			// <
			FUNCTION,			// function
			FUNCTION_CALLBACK,	// callback
			IF,					// if
			WHILE,				// while
			FOR,				// for
			NEW,				// new
			RETURN,				// return
			DUMMY,				// returns a dummy integer for test purposes
			IDENTIFIER			// 'evrything else'
		};
	}

	namespace ksTOKEN_PRIORITY//also represents TOKEN_ID
	{
		enum
		{
			SUBCODE,
			RETURN_STATEMENT,
			FUNCTION_CALL,
			DUMMY,
			STRING,
			GET_FROM_STACK,
			OPERATOR_MEMBER,
			PLACEHOLDER
		};
	}

	//enum TOKEN_ID
	//{
	//	SA_FUNCTION_BEGIN,
	//	SA_FUNCTION_END,
	//	SA_EXPRESSION_END,
	//	SA_PARAMETER_SPLIT,
	//	SA_COMMENT,
	//	SB_OBJECT_BEGIN,
	//	SB_OBJECT_END,
	//	Q_CONST,
	//	T_AUTO,
	//	T_VOID,
	//	T_BOOL,
	//	T_CHAR,
	//	T_INT,
	//	T_LINT,
	//	T_FLOAT,
	//	T_DOUBLE,
	//	T_STRING,
	//	T_TYPE,
	//	T_VERSION,
	//	O_MEMBER_FCALL,
	//	O_SET_EQUAL_TO,
	//	O_ADD,
	//	O_SUBTRACT,
	//	O_MULTIPLY,
	//	O_DIVIDE,
	//	O_CREATE_ADD,
	//	O_CREATE_SUBTRACT,
	//	O_CREATE_DIVIDE,
	//	O_IS_EQUAL_TO,
	//	O_IS_NOT_EQUAL_TO,
	//	O_IS_BIGGER,
	//	O_IS_NOT_BIGGER,
	//	O_IS_BIGGER_OR_EQUAL,
	//	O_IS_NOT_BIGGER_OR_EQUAL,
	//	K_FUNCTION,
	//	K_CALLBACK,
	//	K_IF,
	//	K_WHILE,
	//	K_FOR,
	//	K_NEW,
	//	IDENTIFIER
	//};
}