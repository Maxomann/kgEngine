//_______ALGORITHM_BASE_H_______//

#pragma once

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
	class aIsEqualTo
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
};//kg