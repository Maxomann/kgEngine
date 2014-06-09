//_______ksReturnStatement_______//

#pragma once
#include "../ksToken.h"
#include "../objectSystem/ksLibrary.h"

namespace kg
{
	class ksReturnStatement : public ksToken
	{
		const ksTokenMap::iterator m_elementToReturn;

	public:
		ksReturnStatement( int firstLineOfToken, int lastLineOfToken, const ksTokenMap::iterator& elementToReturn )
			: ksToken( firstLineOfToken, lastLineOfToken ),
			m_elementToReturn( elementToReturn )
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  std::shared_ptr<ksClassInstance>& functionReturnValue ) const
		{
			functionReturnValue = m_elementToReturn->second->execute( library, stack, functionReturnValue );
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
			if( splitCode.at(line).second == ksRAW_TOKEN_ID::RETURN )
				if( splitCode.size() > line + 1 )
				{
					
				}
		}

		virtual int getPriority() const
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

	};
}
