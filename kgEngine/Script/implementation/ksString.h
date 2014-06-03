//_______ksString_______//

#pragma once
#include "../ksToken.h"
#include "../objectSystem/ksLibrary.h"

namespace kg
{
	class ksString : public ksToken
	{
		const std::string m_str;

	public:
		ksString( int firstLineOfToken, int lastLineOfToken, const std::string& str )
			: ksToken( firstLineOfToken, lastLineOfToken ),
			m_str(str)
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library, const std::map<int, std::shared_ptr<ksToken>>& constructedTokens,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  /*only change if this is the return statement */ std::shared_ptr<ksClassInstance>& functionReturnValue )const
		{
			return library.getType<std::string>()->createNewInstance( m_str );
		}

		virtual int getID() const
		{
			return ksTOKEN_PRIORITY::STRING;
		}

	};

	class ksStringConstructor : public ksTokenConstructor
	{
	public:

		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const
		{
			if( splitCode.at( line ).second == ksRAW_TOKEN_ID::_STRING )
			{		
				auto obj = std::make_shared<ksString>( line, line + 2, splitCode.at(line+1).first );
				tokenMap[line] = obj;
				tokenMap[line + 2] = obj;
				return true;
			}
			return false;
		}

		virtual int getPriority() const
		{
			return ksTOKEN_PRIORITY::STRING;
		}

	};
}
