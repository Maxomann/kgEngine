//_______TOKEN_H_______//

#pragma once
#include "stdafx.h"
#include "ksSyntax.h"
#include "ksObject.h"

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

		virtual std::shared_ptr<ksObject> execute( const ksReferenceContainer& refCon )const = 0;

		virtual const int getID()const = 0;
	};

	ABSTRACT class ksTokenConstructor
	{
	public:

		//returns true if Token has been constructed
		virtual bool construct( const std::string& thisToken,
								ksTokenMap& constructedTokens,
								std::vector<std::string>& splitCode,
								int currentLine,
								int bracketCount )const = 0;

		//lowest priotity will be executed first
		virtual const unsigned int getPriority()const = 0;
	};

	enum TOKEN_ID
	{
		BRACKET_OPEN,
		BRACKET_CLOSE,
		IDENTIFIER,
		FUNCTION_CALL
	};
}