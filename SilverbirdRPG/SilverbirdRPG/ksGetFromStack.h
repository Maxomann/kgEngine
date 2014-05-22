//_______ksGetFromStack_______//

#pragma once
#include "ksToken.h"
#include "ksLibrary.h"

namespace kg
{
	class ksGetFromStack : public ksToken
	{
		const std::string& m_name;

	public:
		ksGetFromStack( int firstLineOfToken, int lastLineOfToken, const std::string& objectName )
			: ksToken( firstLineOfToken, lastLineOfToken ),
			m_name(objectName)
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  std::shared_ptr<ksClassInstance>& functionReturnValue ) const
		{
			return stack[m_name];
		}

		virtual int getID() const
		{
			return ksTOKEN_PRIORITY::GET_FROM_STACK;
		}

	};

	class ksGetFromStackConstructor : public ksTokenConstructor
	{
	public:

		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const
		{
			if( splitCode.at( line ).second == ksRAW_TOKEN_ID::_IDENTIFIER )
			{
				tokenMap[line] = std::make_shared<ksGetFromStack>( line, line, splitCode.at( line ).first );
				return true;
			}
			return false;
		}

		virtual int getPriority() const
		{
			return ksTOKEN_PRIORITY::GET_FROM_STACK;
		}

	};
}
