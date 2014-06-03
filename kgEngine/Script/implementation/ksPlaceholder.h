//_______ksPlaceholder_______//

#pragma once
#include "../ksToken.h"
#include "../objectSystem/ksLibrary.h"

namespace kg
{
	class ksPlaceholder : public ksToken
	{
		std::shared_ptr<ksToken> m_obj;

	public:
		ksPlaceholder( int firstLineOfToken, int lastLineOfToken, std::shared_ptr<ksToken> obj )
			: ksToken( firstLineOfToken, lastLineOfToken ),
			m_obj(obj)
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library, const std::map<int, std::shared_ptr<ksToken>>& constructedTokens,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  /*only change if this is the return statement */ std::shared_ptr<ksClassInstance>& functionReturnValue )const
		{
			return(m_obj->execute( library, constructedTokens, stack, functionReturnValue ));
		}

		virtual int getID() const
		{
			return ksTOKEN_PRIORITY::PLACEHOLDER;
		}

	};

}
