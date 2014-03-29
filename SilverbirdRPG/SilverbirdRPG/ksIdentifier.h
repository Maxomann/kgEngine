//_______IDENTIFIER_H_______//

#pragma once
#include "ksToken.h"

namespace kg
{
	namespace token
	{
		class Identifier : public ksToken
		{
			const std::string m_identifier;

		public:
			Identifier( const int endOfToken, const std::string identifier )
				:m_identifier( identifier ),
				ksToken( endOfToken )
			{ }

			virtual std::shared_ptr<ksObject> execute( const ksReferenceContainer& refCon ) const
			{
				return refCon.stack[m_identifier];
			}

			const std::string& getIdentifier()const
			{
				return m_identifier;
			}

			virtual const int getID() const
			{
				return TOKEN_ID::IDENTIFIER;
			}
		};

		class IdentifierConstructor : public ksTokenConstructor
		{
		public:
			static const int PRIORITY = 10;

			virtual bool construct( const ksTokenConstructorMap& tokenConstructors,
									const std::string& thisToken,
									ksTokenMap& constructedTokens,
									std::vector<std::string>& splitCode,
									int currentLine )const
			{
				if( constructedTokens[currentLine] == nullptr )
				{
					constructedTokens[currentLine] = std::make_shared<Identifier>( currentLine,
																				   thisToken );
					return true;
				}
				return false;
			}

			virtual const unsigned int getPriority() const
			{
				return PRIORITY;
			}
		};
	}
}