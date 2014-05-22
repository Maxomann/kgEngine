//_______ksString_______//

#pragma once
#include "ksToken.h"
#include "ksLibrary.h"

namespace kg
{
	class ksString : public ksToken
	{
		const std::string m_str;

	public:
		ksString( int firstLineOfToken, int lastLineOfToken, const std::string& str )
			: ksToken( firstLineOfToken, lastLineOfToken, lastLineOfToken ),
			m_str(str)
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  std::shared_ptr<ksClassInstance>& functionReturnValue ) const
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
				std::string str;

				int i = 0;
				while( splitCode.at( line + i ).second != ksRAW_TOKEN_ID::_STRING )
				{
					str += splitCode.at( line + i ).first;
					i++;
				}
				
				auto obj = std::make_shared<ksString>( line, line + i + 1, str );
				tokenMap[line] = obj;
				tokenMap[line + i + 1] = obj;
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
