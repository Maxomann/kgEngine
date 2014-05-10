//_______ksSubcode_______//

#pragma once
#include "ksToken.h"
#include "ksLibrary.h"

namespace kg
{
	class ksSubcode : public ksToken
	{
		ksCode m_subCode;

	public:
		ksSubcode( int firstLineOfToken,
				   int lastLineOfToken,
				   const ksTokenConstructorPriorityMap& tokenConstructors,
				   ksSplitCodeVector& subCode )
			: ksToken( firstLineOfToken, lastLineOfToken ),
			m_subCode( tokenConstructors, subCode )
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  std::shared_ptr<ksClassInstance>& functionReturnValue ) const
		{
			return m_subCode.execute( library, stack );
		}

		virtual int getID() const
		{
			return ksTOKEN_PRIORITY::SUBCODE;
		}

	};

	class ksSubcodeConstructor : public ksTokenConstructor
	{
	public:

		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const
		{
			if( splitCode.at( line ).second == ksRAW_TOKEN_ID::_OBJECT_BEGIN )
			{
				//by reference
				std::vector< const std::pair<std::string, int>> subCode;

				int bracketCount = 0;//counts { and }

				//iterate through code
				for( int x = 0; true; ++x )
				{
					bool isBracket = false;

					const std::pair<std::string, int>& it = splitCode.at( line + x );
					if( it.second == ksRAW_TOKEN_ID::_OBJECT_BEGIN )
					{
						bracketCount++;
						isBracket = true;
					}
					if( it.second == ksRAW_TOKEN_ID::_OBJECT_END )
					{
						bracketCount--;
						isBracket = true;
					}
					if( bracketCount == 0 )
					{
						tokenMap[line] = std::make_shared<ksSubcode>( line, line + x, tokenConstructors, subCode );
						break;
					}
#ifdef _DEBUG
					if( x > 50000 )
						REPORT_ERROR_SCRIPT( "debug: x too high" );
#endif
					if(!isBracket )
						subCode.push_back( it );
				}
				
				return true;
			}
			else
				return false;
		}

		virtual int getPriority() const
		{
			return ksTOKEN_PRIORITY::SUBCODE;
		}

	};
}
