//_______CODE_______//

#pragma once
#include "stdafx.h"
#include "ksSyntax.h"
#include "ksToken.h"
#include "aException.h"

namespace kg
{
	class ksCode
	{
		ksTokenMap m_constructedTokens;

		ksSplitCodeVector m_generateSplitCode( const ksRawTokenMap& rawTokens,
											   const std::string& code )const;

		void m_constructTokens( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode );

	public:
		ksCode( const ksTokenConstructorPriorityMap& tokenConstructors,
				const ksRawTokenMap& rawTokens,
				const std::string& code );

		ksCode( const ksTokenConstructorPriorityMap& tokenConstructors,
				const ksSplitCodeVector& splitCode );

		std::shared_ptr<kg::ksClassInstance> execute( ksLibrary& library,
													  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack )const;
	};
}