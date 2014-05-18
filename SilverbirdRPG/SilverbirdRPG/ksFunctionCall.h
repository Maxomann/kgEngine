//_______ksFunctionCall_______//

#pragma once
#include "ksToken.h"
#include "ksLibrary.h"

namespace kg
{
	class ksFunctionCall : public ksToken
	{
	public:
		ksFunctionCall( int firstLineOfToken, int lastLineOfToken, const std::string& functionName )
			: ksToken( firstLineOfToken, lastLineOfToken )
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  std::shared_ptr<ksClassInstance>& functionReturnValue ) const
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

		virtual int getID() const
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

	};

	class ksFunctionCallConstructor : public ksTokenConstructor
	{
	public:

		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const
		{
			if( splitCode.at( line ).second == ksRAW_TOKEN_ID::_IDENTIFIER )
			{
				tokenMap[line] = std::make_shared<ksFunctionCall>( line, line, splitCode.at( line ).first );
			}
		}

		virtual int getPriority() const
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

	};
}
