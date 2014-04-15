//_______CODE_______//

#pragma once
#include "stdafx.h"
#include "ksSyntax.h"
#include "ksToken.h"

namespace kg
{
	class ksCode
	{
		//TODO
		std::vector<std::shared_ptr<ksClassInstance>> m_stack;

		ksTokenMap m_constructedTokens;

		ksSplitCodeVector m_generateSplitCode( const ksRawTokenMap& rawTokens,
											   const std::string& code )const;

		void m_constructTokens( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode );

	public:
		ksCode( const ksTokenConstructorPriorityMap& tokenConstructors,
				const ksRawTokenMap& rawTokens,
				ksCodeVector& subCodeContainer,
				const std::string& code );

		ksCode( const ksTokenConstructorPriorityMap& tokenConstructors,
				ksCodeVector& subCodeContainer,
				const ksSplitCodeVector& code );

		std::shared_ptr<kg::ksClassInstance> execute( ksLibrary& library,
													  const std::map<std::string, ksFunctionMaster>& availableFunctions,
													  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack )const;
	};
}