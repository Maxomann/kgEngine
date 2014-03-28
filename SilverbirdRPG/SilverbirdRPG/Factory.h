//_______FACTORY_H_______//

#pragma once
#include"stdafx.h"
#include"ResourceManagement.h"

namespace kg
{
	template< class T >
	class Factory
	{
	protected:
		ResourceManagement*	r_resourceManagement;

		int					m_id = -1;

		//ATTENTION: Set m_id
		virtual void			m_loadFromFile( const std::string& path ) = 0;

	public:
		Factory( ResourceManagement& resourceManagement )
			:r_resourceManagement( &resourceManagement )
		{ };

		//if it returns -1, something went wrong
		inline int getId()
		{
			return m_id;
		};

		//Can't declare it here but don't forget!
		//virtual T*	getObject() = 0;
	};
}