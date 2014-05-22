//_______ksPlaceholder_______//

#pragma once
#include "ksToken.h"
#include "ksLibrary.h"

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

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  std::shared_ptr<ksClassInstance>& functionReturnValue ) const
		{
			return(m_obj->execute( library, stack, functionReturnValue ));
		}

		virtual int getID() const
		{
			return ksTOKEN_PRIORITY::PLACEHOLDER;
		}

	};

}
