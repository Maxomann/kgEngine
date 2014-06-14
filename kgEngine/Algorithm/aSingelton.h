//_______SINGELTON_H_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	template< class T >
	struct ALGORITHM_API aSingelton
	{
		static T& getInstance()
		{
			static T inst;
			return inst;
		};
	};
};//kg