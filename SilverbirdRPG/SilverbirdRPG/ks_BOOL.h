//_______T_BOOL_______//

#include "ksToken.h"

namespace kg
{
	namespace ksToken
	{
		class BOOL : public ksToken
		{
		public:
			BOOL( const int endOfToken )
				: ksToken( endOfToken )
			{ }

			virtual std::shared_ptr<ksClassInstance> execute( const ksReferenceContainer& refCon ) const
			{
				throw std::logic_error( "The method or operation is not implemented." );
			}

			virtual const int getID() const
			{
				return TOKEN_ID::T_BOOL;
			}
		};

		class BOOL_CONSTRUCTOR : public ksTokenConstructor
		{
		public:
			virtual bool construct( const ksTokenConstructorMap& tokenConstructors,
									const std::string& thisToken,
									ksTokenMap& constructedTokens,
									std::vector<std::string>& splitCode,
									int currentLine ) const
			{
				throw std::logic_error( "The method or operation is not implemented." );
			}

			virtual const unsigned int getPriority() const
			{
				return TOKEN_PRIORITY::STANDART_TYPE;
			}

		};

	}
}