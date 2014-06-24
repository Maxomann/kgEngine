//_______EXTENDABLE_______//

#pragma once

//Include über <aException.h> nicht möglich
#include "stdafx.h"
#include "pExtension.h"

namespace kg
{
	class pExtendable
	{
	protected:
		std::unordered_map<size_t, std::shared_ptr<pExtension>> m_extensions;

	public:
		// T=type of class that derived from pExtension
		template<class T>
		PLUGIN_API void addExtension( std::shared_ptr<pExtension>& extension )
		{
			m_extensions[typeid(T).hash_code()] = extension;
		}

		// DON'T! delete the given pointer
		// You must not store references to the given object
		// the given object is the instance held by the Extension, NOT the Extension itself
		template<class T>
		PLUGIN_API std::shared_ptr<T> getExtension()const
		{
			try
			{
				return static_pointer_cast< T >(m_extensions.at( typeid(T).hash_code() ));
			}
			catch( std::out_of_range e )
			{
				REPORT_ERROR_PLUGIN( "Extension class: " + typeid(T).name() + " is not available" );
			}
		}

		PLUGIN_API virtual void initExtensions() = 0;
	};

	class PLUGIN_API pExtensionProviderInterface
	{
	public:
		virtual void addExtensionTo( pExtendable& extendable )const = 0;
	};

	// T= class derived from pExtension
	template<class T>
	class PLUGIN_API pExtensionProvider : public pExtensionProviderInterface
	{
	public:
		void addExtensionTo( pExtendable& extendable )const
		{
			extendable.addExtension<T>( std::static_pointer_cast< pExtension >(std::make_shared<T>()) );
		};
	};
}
