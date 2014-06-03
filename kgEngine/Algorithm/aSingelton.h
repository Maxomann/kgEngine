//_______SINGELTON_H_______//

#pragma once

namespace kg
{
	template< class T >
	struct aSingelton
	{
		static T& getInstance()
		{
			static T inst;
			return inst;
		};
	};
};//kg