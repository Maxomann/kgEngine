//_______SCRIPT_H_______//

#pragma once
#include "stdafx.h"
#include "ksCode.h"
#include "ksObject.h"
#include "aException.h"

namespace kg
{
	class ksScript
	{
		ksTokenConstructorMap& r_tokenConstructors;
		ksFunctionMap& r_availableFunctions;
		ksParentMap& r_availableCppObjectTypes;

		ksObjectMap m_stack;
		std::vector<ksCode> m_subCode;

		std::string m_code;

	public:
		ksScript( ksTokenConstructorMap& tokenConstructors,
				  ksFunctionMap& availableFunctions,
				  ksParentMap& availableCppObjectTypes );

		bool loadFromFile( const std::string& path );
		bool loadFromString( const std::string& code );

		bool isLoaded();

		void interpret();
	};
}