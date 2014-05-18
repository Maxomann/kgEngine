//_______ksReturnStatement_______//

#pragma once
#include "ksToken.h"
#include "ksLibrary.h"

//#include "ksSubcode.h"

namespace kg
{
	class ksReturnStatement : public ksToken
	{
		std::shared_ptr<ksToken>& m_retVal;

	public:
		ksReturnStatement( int firstLineOfToken,
						   int lastLineOfToken,
						   std::shared_ptr<ksToken>& retVal )
						   : ksToken( firstLineOfToken, lastLineOfToken ),
						   m_retVal( retVal )

		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  std::shared_ptr<ksClassInstance>& functionReturnValue ) const
		{
			functionReturnValue = m_retVal->execute( library,
													 stack,
													 functionReturnValue );
			return nullptr;
		}

		virtual int getID() const
		{
			return ksTOKEN_PRIORITY::RETURN_STATEMENT;
		}

	};

	class ksReturnStatementConstructor : public ksTokenConstructor
	{
	public:

		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const
		{
			if( splitCode.at( line ).second == ksRAW_TOKEN_ID::_RETURN )
			{
				if( splitCode.size() >= line + 2 )
				{
					tokenMap[line] = std::make_shared<ksReturnStatement>( line, line, tokenMap[line + 1] );
					return true;
				}
				else
					return false;
			}

			return false;
		}

		virtual int getPriority() const
		{
			return ksTOKEN_PRIORITY::RETURN_STATEMENT;
		}

	};
}
