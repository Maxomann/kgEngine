//_______RESOURCE_MANAGEMENT_H_______//

#pragma once
#include"stdafx.h"
#include "aException.h"

namespace kg
{
	class Resource
	{
	public:
		virtual void loadFromFile( const std::string& path ) = 0;
	};

	class ResourceManagement
	{
	private:
		std::unordered_map< std::string, std::unordered_map<size_t, std::shared_ptr<void>> >m_resources;

	public:

		//Path begins with the location of the resource folder
		//PATH: (Folder of main.exe)/ResourceWrappers + relativePath
		template< class T >
		std::shared_ptr<T> getResourceFromResourceFolder( std::string relativePath )
		{
			return getResource<T>( RESOURCE_FOLDER + relativePath );
		}

		//Template argument is the type, NOT A POINTER TO IT!!!
		//getResource<sf::Texture>  == OK
		//getResource<sf::Texture*> == NOT WORKING
		//
		//class T must have a function like this:
		//void T::loadFromFile(const std::string& path)
		//YOU CAN INHERIT FROM SHARED::RESOURCE FOR THAT
		template< class T >
		std::shared_ptr<T> getResource( std::string path )
		{
			const size_t typeID = typeid(T).hash_code();

			auto it = m_resources.find( path );

			//wenn Element nicht vorhanden
			if( it == m_resources.end() )
			{
				auto res = std::make_shared<T>();
				//neues element und signatur einfügen
				m_resources[path][typeID] = std::static_pointer_cast< void >(res);
				if( !res->loadFromFile( path ) )
					REPORT_ERROR( "File: " + path + "could not be loaded" );
				return res;
			}
			//wenn element vorhanden
			else
			{
				//nach signatur suchen
				auto secondIt = it->second.find( typeID );
				//wenn element aber NICHT signatur vorhanden
				if( secondIt == it->second.end() )
				{
					auto res = std::make_shared<T>();
					//neue signatur (kein neues element) einfügen
					it->second[typeID] = std::static_pointer_cast< void >(res);
					if( !res->loadFromFile( path ) )
						REPORT_ERROR( "File: " + path + "could not be loaded" );
					return res;
				}
				//wenn element und signatur vorhanden
				else
				{
					return std::static_pointer_cast< T >(secondIt->second);
				}
			}
		}

		static const char RESOURCE_FOLDER[];
		static const char PLUGIN_FOLDER_CLIENT[];
		static const char PLUGIN_FOLDER_SERVER[];
	};
}
