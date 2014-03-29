//_______FUNCTION_CALL_H_______//

#pragma once
#include "ksToken.h"
#include "aException.h"

namespace kg
{
	namespace token
	{
		class FunctionCall : public ksToken
		{
			const std::string m_functionName;

		public:
			FunctionCall( const int endOfToken, const std::string& functionName )
				:ksToken( endOfToken ),
				m_functionName( functionName )
			{ }

			virtual std::shared_ptr<ksObject> execute( const ksReferenceContainer& refCon ) const
			{
#pragma message( "class FunctionCall: make parameter possible" )
				return refCon.availableFunctions.at( m_functionName )(ksObjectVector());
			}

			virtual const int getID() const
			{
				return TOKEN_ID::FUNCTION_CALL;
			}
		};

		class FunctionCallConstructor : public ksTokenConstructor
		{
		public:
			static const int PRIORITY = 11;

			virtual bool construct( const ksTokenConstructorMap& tokenConstructors,
									const std::string& thisToken,
									ksTokenMap& constructedTokens,
									std::vector<std::string>& splitCode,
									int currentLine )const
			{
				auto it = begin( constructedTokens );
				for( int i = 0; i < currentLine + 1; ++i )
				{
					it++;
					if( it == end( constructedTokens ) )
						return false;
				}

				if( constructedTokens[currentLine]->getID() == TOKEN_ID::IDENTIFIER &&
					constructedTokens[currentLine + 1]->getID() == TOKEN_ID::BRACKET_OPEN )
				{
					int internalBracketCount = 0;
					for( int i = currentLine + 2; true; i++ )
					{
						if( constructedTokens[i]->getID() == BRACKET_OPEN )
						{
							internalBracketCount++;
						}
						else if( constructedTokens[i]->getID() == BRACKET_CLOSE )
						{
							if( internalBracketCount == 0 )
							{
								constructedTokens[currentLine] = std::make_shared<FunctionCall>( i, thisToken );
								return true;
							}
							else
							{
								internalBracketCount--;
							}
						}

						//Debug stuff
						if( i > 1000 )
							REPORT_ERROR_SCRIPT( "UnrealisticNumber" );
					}
				}
				else
					return false;
			}

			virtual const unsigned int getPriority() const
			{
				return PRIORITY;
			}
		};
	}
}