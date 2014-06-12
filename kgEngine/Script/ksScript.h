//_______SCRIPT_______//

#pragma once
#include "stdafx.h"
#include "ksCode.h"
#include "objectSystem/ksLibrary.h"

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

		std::shared_ptr<ksClassInstance> interpret();

		bool isInterpreted()const;

		bool isLoaded()const;
	};

}
