//_______CODE_H_______//

#pragma once
#include "stdafx.h"
#include "ksSyntax.h"
#include "ksToken.h"

namespace kg
{
	class ksCode
	{
		std::vector<std::string> m_splitCode;
		std::vector<ksCode> m_subCode;

		ksTokenMap m_tokens;

		void m_constructTokens( const ksTokenConstructorMap& tokenConstructors );
		void m_genereateSubCode( const ksTokenConstructorMap& tokenConstructors,
								 std::string& code );

	public:
		ksCode( const ksTokenConstructorMap& tokenConstructors,
				const std::string& code );

		void execute( const ksReferenceContainer& refCon );

#ifdef _DEBUG
		const std::string toString()const;
#endif
	};
}