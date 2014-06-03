//_______ALGORITHM_RANDOM_H_______//

#pragma once
#include<random>
#include "stdafx.h"

namespace kg
{
	template< class T = int >
	class SCRIPT_API aRandomGenerator_Int
	{
	protected:
		inline aRandomGenerator_Int()
		{ };
		inline aRandomGenerator_Int( const aRandomGenerator_Int< T >& obj )
		{ };

		static inline bool m_reSeed( std::random_device &rdv, std::mt19937 &rng )
		{
			rng.seed( rdv() );
			return true;
		};

	public:

		static inline T getRandom()
		{
			static std::random_device rdv;
			static std::mt19937 rng;
			static const bool b = aRandomGenerator_Int::m_reSeed( rdv, rng );

			return std::uniform_int_distribution< T >()(rng);
		};
		static inline T getRandom( T from, T to )
		{
			static std::random_device rdv;
			static std::mt19937 rng;
			static const bool b = aRandomGenerator_Int::m_reSeed( rdv, rng );

			return std::uniform_int_distribution< T >( from, to )(rng);
		};
	};
};//kg
