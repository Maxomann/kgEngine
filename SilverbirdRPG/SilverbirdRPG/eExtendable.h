//_______EXTENDABLE_H_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class eExtendable
	{
	private:
		std::map<size_t, std::shared_ptr<void>>	m_extensions;

	public:
		template< class T > void registerExtension();

		template< class T >
		const std::shared_ptr<T>& getExtension()const;
	};

	template< class T >
	void kg::eExtendable::registerExtension()
	{
		m_extensions[typeid(T).hash_code()] = std::make_shared<T>();
	}

	//returns nullptr if extension T has not been registred
	template< class T >
	const std::shared_ptr<T>& kg::eExtendable::getExtension()const
	{
		return std::static_pointer_cast< T >(m_extensions.at(typeid(T).hash_code()));
	}

}