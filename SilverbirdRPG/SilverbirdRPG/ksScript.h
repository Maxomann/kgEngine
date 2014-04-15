//_______SCRIPT_______//

#include "stdafx.h"
#include "ksCode.h"
#include "aException.h"

namespace kg
{
	class ksScript
	{
		ksLibrary& r_library;
		const ksTokenConstructorPriorityMap& r_tokenConstructors;
		const ksRawTokenMap& r_rawTokens;


		bool m_isInterpreted = false;

		std::string m_code;

		std::map<std::string, std::shared_ptr<ksClassInstance>> m_stack;

	public:
		ksScript( ksLibrary& library,
				  const ksTokenConstructorPriorityMap& tokenConstructors,
				  const ksRawTokenMap& rawTokens );

		bool loadFromFile( const std::string& path );
		bool loadFromString( const std::string& code );

		void interpret();

		bool isInterpreted()const;

		bool isLoaded()const;
	};

}