//_______FUNCTION_______//

#include "stdafx.h"

namespace kg
{
	
	template< class _function, class ...Args >
	class ksMemberFunctionWrapper
	{
		_function m_function;

	public:
		ksMemberFunctionWrapper( const std::string& ksRetType, _function memFn );



	};
}