//_______TOKEN_______//

#pragma once
#include "stdafx.h"
#include "ksSyntax.h"

namespace kg
{
	class ksTokenConstructor
	{
	public:
		// return true on success
		// construct the token in tokenMap[line]
		// place a pointer to the token in tokenMap[lastLineOfToken]
		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const = 0;

		// 0=highest priority
		virtual int getPriority()const = 0;
	};

	class ksToken
	{
		const int m_lastLineOfToken = -1;

		const int m_firstLineOfToken = -1;

	public:
		ksToken( int firstLineOfToken, int lastLineOfToken );

		//return nullptr if returnType==void
		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  const std::map<int, std::shared_ptr<ksToken>>& constructedTokens,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  /*only change if this is the return statement */ std::shared_ptr<ksClassInstance>& functionReturnValue )const = 0;

		int getLastLine()const;
		int getFirstLine()const;

		virtual int getID()const = 0;
	};
}