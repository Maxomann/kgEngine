//_______TOKEN_______//

#pragma once
#include "stdafx.h"
#include "ksSyntax.h"
#include "ksLibrary.h"

namespace kg
{
	class ksTokenConstructor
	{
	public:
		// return true on success
		// construct the token in tokenMap[line]
		virtual bool construct( const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line )const = 0;

		// 0=highest priority
		virtual int getPriority()const=0;
	};

	class ksToken
	{
		const int m_lastlineOfToken;

	public:
		ksToken( int lastLineOfToken );

		//return nullptr if returnType==void
		virtual std::shared_ptr<ksClassInstance> execute( const ksReferenceContainer& refCon )const=0;

		int getLastLine()const;

		virtual int getID()const=0;
	};

}