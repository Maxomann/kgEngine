//_______TOKEN_H_______//

#pragma once
#include "stdafx.h"
#include "ksSyntax.h"
#include "ksClass.h"
#include "aException.h"

namespace kg
{
	ABSTRACT class ksToken
	{
	private:
		const unsigned int m_endOfToken;

	public:
		ksToken( const int endOfToken );

		//returns the last line number of this token
		unsigned int getEndOfToken()const;

		virtual std::shared_ptr<ksClassInstance> execute( const ksReferenceContainer& refCon )const = 0;

		virtual const int getID()const = 0;
	};

	ABSTRACT class ksTokenConstructor
	{
	public:

		//returns true if Token has been constructed
		virtual bool construct( const ksTokenConstructorMap& tokenConstructors,
								const std::string& thisToken,
								ksTokenMap& constructedTokens,
								std::vector<std::string>& splitCode,
								int currentLine )const = 0;

		//lowest priotity will be executed first
		virtual const unsigned int getPriority()const = 0;
	};

	enum TOKEN_PRIORITY
	{
		SYNTAX_ONLY_a,
		SYNTAX_ONLY_b,
		QUALIFIER,
		STANDART_TYPE,
		IDENTIFIER_FCALL,
		OPERATOR,
		KEYWORD
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
		I_IDENTIFIER_FCALL,
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
		K_NEW
	};
}