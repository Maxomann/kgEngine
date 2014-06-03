//_______ksNew_______//

#pragma once
#include "../ksToken.h"
#include "../objectSystem/ksLibrary.h"

namespace kg
{
	class ksNew : public ksToken
	{
	public:
		ksNew( int firstLineOfToken, int lastLineOfToken )
			: ksToken( firstLineOfToken, lastLineOfToken )
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library, const std::map<int, std::shared_ptr<ksToken>>& constructedTokens,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  /*only change if this is the return statement */ std::shared_ptr<ksClassInstance>& functionReturnValue )const
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

		virtual int getID() const
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

	};

	// new type name;
	// new type name( args );
	// 
	// new int i;
	// new obj o( 33, 525 );
	class ksNewConstructor : public ksTokenConstructor
	{
	public:

		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const
		{
			if( splitCode.at( line ).second == ksRAW_TOKEN_ID::_NEW )
			{
				//no constructor args
				if( splitCode.at( line + 3 ).second != ksRAW_TOKEN_ID::_FUNCTION_BEGIN )
				{

				}
				//with args
				else
				{

				}
			}
		}

		virtual int getPriority() const
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

	};
}
