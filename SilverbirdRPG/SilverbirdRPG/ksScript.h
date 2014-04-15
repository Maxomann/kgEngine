//_______SCRIPT_______//

#include "stdafx.h"
#include "ksCode.h"
#include "aException.h"
#include "ksLibrary.h"

namespace kg
{
	class ksScript
	{
		ksLibrary& r_library;

		bool m_isInterpreted = false;

		std::string m_code;

		std::map<std::string, std::shared_ptr<ksClassInstance>> m_stack;

	public:
		ksScript( ksLibrary& library );

		bool loadFromFile( const std::string& path );
		bool loadFromString( const std::string& code );

		void interpret();

		bool isInterpreted()const;

		bool isLoaded()const;
	};

	void ksRegisterStandartTypes( ksLibrary& library )
	{
		//TODO
	}
	void ksRunScript( ksLibrary& library,
					  const ksTokenConstructorPriorityMap& tokenConstructors,
					  const ksRawTokenMap& rawTokens,
					  const std::string& path )
	{
		ksScript script( library, tokenConstructors, rawTokens );
		script.loadFromFile( path );
		script.interpret();
	}

}