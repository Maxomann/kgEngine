//_______ALGORITHM_BASE_H_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	//////////////////////////////////////////////////
	///
	/// \brief
	/// template function created for use in some std::algorithm.
	/// You can use it like this:
	///
	/// \code
	/// std::any_of( container.begin(), container.end(), IsEqualTo<char>( 'a' ) );
	/// \endcode
	///
	//////////////////////////////////////////////////

	template< class T >
	class ALGORITHM_API aIsEqualTo
	{
	public:
		inline aIsEqualTo( T one ) : m_one( one )
		{ };

		inline bool operator() ( T two )
		{
			return m_one == two;
		};

	private:
		T m_one;
	};


	template<class T>
	//MAY NOT WORK CORRECTLY!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ALGORITHM_API sf::Vector2<T> rotatePointAroundPoint( sf::Vector2<T>pointToRotate,
														 T degrees,
														 sf::Vector2<T>pointToRotateAround = { 0, 0 })
	{
		sf::Vector2<T> transformedPoint;

		//A.x' = (A.x-B.x) * cos(C) - (A.y-B.y) * sin(C) + B.x
		//A.y' = (A.y-B.y) * cos(C) + (A.x-B.x) * sin(C) + B.y
		transformedPoint.x =
			((pointToRotate.x - pointToRotateAround.x)*cos( degrees ))
			- ((pointToRotate.y - pointToRotateAround.y)*sin( degrees ))
			+ pointToRotateAround.x;
		transformedPoint.y =
			((pointToRotate.y - pointToRotateAround.y)*cos( degrees ))
			+ ((pointToRotate.x - pointToRotateAround.x)*sin( degrees ))
			+ pointToRotateAround.y;

		return transformedPoint;
	}

};//kg