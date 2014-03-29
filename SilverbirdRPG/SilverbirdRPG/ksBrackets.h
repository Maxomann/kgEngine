//_______BRACKETS_H_______//

#pragma once
#include "ksToken.h"

namespace kg
{
	namespace token
	{
		class BracketOpen : public ksToken
		{
		public:
			BracketOpen( const int endOfToken )
				:ksToken( endOfToken )
			{ }

			virtual std::shared_ptr<ksObject> execute( const ksReferenceContainer& refCon ) const
			{
				return nullptr;
			}

			virtual const int getID() const
			{
				return TOKEN_ID::BRACKET_OPEN;
			}
		};

		class BracketOpenConstructor : public ksTokenConstructor
		{
		public:
			static const char TOKEN = '(';
			static const int PRIORITY = 0;

			virtual bool construct( const std::string& thisToken,
									ksTokenMap& constructedTokens,
									std::vector<std::string>& splitCode,
									int currentLine,
									int bracketCount )const
			{
				if( thisToken.at( 0 ) == TOKEN )
				{
					constructedTokens[currentLine] = std::make_shared<BracketOpen>( currentLine );
					return true;
				}
				else
					return false;
			}

			virtual const unsigned int getPriority() const
			{
				return PRIORITY;
			}
		};

		class BracketClose : public ksToken
		{
		public:
			BracketClose( const int endOfToken )
				:ksToken( endOfToken )
			{ }

			virtual std::shared_ptr<ksObject> execute( const ksReferenceContainer& refCon ) const
			{
				return nullptr;
			}

			virtual const int getID() const
			{
				return TOKEN_ID::BRACKET_CLOSE;
			}
		};

		class BracketCloseConstructor : public ksTokenConstructor
		{
		public:
			static const char TOKEN = ')';
			static const int PRIORITY = 0;

			virtual bool construct( const std::string& thisToken,
									ksTokenMap& constructedTokens,
									std::vector<std::string>& splitCode,
									int currentLine,
									int bracketCount )const
			{
				if( thisToken.at( 0 ) == TOKEN )
				{
					constructedTokens[currentLine] = std::make_shared<BracketClose>( currentLine );
					return true;
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