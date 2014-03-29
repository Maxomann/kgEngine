//_______STATIC_TOKEN_______//

#include "ksToken.h"

namespace kg
{
	namespace token
	{
		class StaticToken : public ksToken
		{
			const int m_id;

		public:
			StaticToken( const int id, const int endOfToken )
				: ksToken( endOfToken ),
				m_id(id)
			{ }

			virtual std::shared_ptr<ksObject> execute( const ksReferenceContainer& refCon ) const
			{
				return nullptr;
			}

			virtual const int getID() const
			{
				return m_id;
			}
		};

		class StaticTokenConstructor : public ksTokenConstructor
		{
			const int m_priority;
			const int m_id;
			const std::string m_token;

		public:
			StaticTokenConstructor( const int priority,
									const int id,
									const std::string token )
									:m_priority(priority),
									m_id(id),
									m_token( token )
			{ }

			virtual bool construct( const ksTokenConstructorMap& tokenConstructors,
									const std::string& thisToken,
									ksTokenMap& constructedTokens,
									std::vector<std::string>& splitCode,
									int currentLine ) const
			{
				if( thisToken == m_token && constructedTokens[currentLine]==nullptr )
				{
					constructedTokens[currentLine] = std::make_shared<StaticToken>( m_id, currentLine );
					return true;
				}
				return false;
			}

			virtual const unsigned int getPriority() const
			{
				return m_priority;
			}

		};

	}
}