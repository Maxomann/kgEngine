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

	// first: token
	// second: tokenId
	typedef std::map<std::string, int> ksRawTokenMap;

	typedef std::vector<ksCode> ksCodeVector;

	typedef std::vector<std::pair<std::string, int>> ksSplitCodeVector;

	// first: first line the token takes care of
	// second: token
	typedef std::map<int, std::shared_ptr<ksToken>> ksTokenMap;

	// first: priority
	// second: tokenConstructors with that priority
	typedef std::map<int, std::vector<std::shared_ptr<ksTokenConstructor>>> ksTokenConstructorPriorityMap;



	struct ksReferenceContainer
	{
		std::map<std::string, std::shared_ptr<ksClassInstance>>& parameterStack;

		//for ksScript internal functions to return a value
		std::shared_ptr<ksClassInstance> returnValue;

		ksLibrary& library;
	};



	enum TOKEN_ID
	{
		SA_FUNCTION_BEGIN,
		SA_FUNCTION_END,
		SA_EXPRESSION_END,
		SA_PARAMETER_SPLIT,
		SA_COMMENT,
		SB_OBJECT_BEGIN,
		SB_OBJECT_END,
		Q_CONST,
		T_AUTO,
		T_VOID,
		T_BOOL,
		T_CHAR,
		T_INT,
		T_LINT,
		T_FLOAT,
		T_DOUBLE,
		T_STRING,
		T_TYPE,
		T_VERSION,
		O_MEMBER_FCALL,
		O_SET_EQUAL_TO,
		O_ADD,
		O_SUBTRACT,
		O_MULTIPLY,
		O_DIVIDE,
		O_CREATE_ADD,
		O_CREATE_SUBTRACT,
		O_CREATE_DIVIDE,
		O_IS_EQUAL_TO,
		O_IS_NOT_EQUAL_TO,
		O_IS_BIGGER,
		O_IS_NOT_BIGGER,
		O_IS_BIGGER_OR_EQUAL,
		O_IS_NOT_BIGGER_OR_EQUAL,
		K_FUNCTION,
		K_CALLBACK,
		K_IF,
		K_WHILE,
		K_FOR,
		K_NEW,
		IDENTIFIER
	};
}