//_______ksDummy_______//

#pragma once
#include "ksToken.h"
#include "ksLibrary.h"
#include "aRandom.h"

namespace kg
{
	class ksDummy : public ksToken
	{
	public:
		ksDummy( int firstLineOfToken, int lastLineOfToken )
			: ksToken( firstLineOfToken, lastLineOfToken, lastLineOfToken )
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  std::shared_ptr<ksClassInstance>& functionReturnValue ) const
		{
			return library.getType<int>()->createNewInstance( aRandomGenerator_Int<int>::getRandom() );
		}

		virtual int getID() const
		{
			return ksTOKEN_PRIORITY::DUMMY;
		}
	};

	class ksDummyConstructor : public ksTokenConstructor
	{
	public:

		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const
		{
			if( splitCode.at( line ).second == ksRAW_TOKEN_ID::_DUMMY )
			{
				tokenMap[line] = std::make_shared<ksDummy>( line, line );
				return true;
			}
			else
				return false;
		}

		virtual int getPriority() const
		{
			return ksTOKEN_PRIORITY::DUMMY;
		}

	};
}
