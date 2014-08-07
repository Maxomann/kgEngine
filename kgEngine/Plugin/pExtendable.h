//_______EXTENDABLE_______//

#pragma once

//Include über <aException.h> nicht möglich
#include "stdafx.h"

namespace kg
{
	class pExtension;
	class pPluginManager;

	class pExtendable
	{
	protected:
		/// The loaded extensions.
		std::unordered_map<size_t, std::shared_ptr<pExtension>> m_extensions;

	public:

		/// Adds an extension.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @typeparam	T	type of class that derived from pExtension
		/// @param [in,out]	extension	The extension.
		template<class T>
		PLUGIN_API void addExtension( std::shared_ptr<pExtension>& extension )
		{
			m_extensions[typeid(T).hash_code()] = std::move(extension);
		}

		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @typeparam	T	Type of the Extension to get.
		///
		/// @return	The extension.
		template<class T>
		PLUGIN_API std::shared_ptr<T> getExtension()
		{
			try
			{
				return std::static_pointer_cast< T >(m_extensions.at( typeid(T).hash_code() ));
			}
			catch( std::out_of_range e )
			{
				REPORT_ERROR_PLUGIN( "Extension class: " + typeid(T).name() + " is not available" );
			}
		}

		/// Initializes the extensions.
		///
		/// @author	Kay
		/// @date	07.08.2014
		///
		/// @param [in,out]	pluginManager	Manager for plug in.
		PLUGIN_API virtual void initExtensions( pPluginManager& pluginManager ) = 0;
	};
}
