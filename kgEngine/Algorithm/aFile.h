//_______CONFIG_FILE_______//

#pragma once
#include "stdafx.h"
#include "aException.h"

namespace kg
{
	ALGORITHM_API std::string aLoadFileToString( const std::string& path );

	//don't forget to DELETE char*
	ALGORITHM_API char* aLoadFileToCharPointer( const std::string& path );

	//File will be deleted before writing
	ALGORITHM_API void aSaveStringToFile( const std::string& path, const std::string& data );

	class aDataByIdentifierFile
	{
		std::map<std::string, std::string> m_data;

	public:

		ALGORITHM_API bool loadFromFile( const std::string& path );

		ALGORITHM_API void saveToFile( const std::string& path );
		ALGORITHM_API std::string toString()const;

		ALGORITHM_API const std::map<std::string, std::string>& getAllData();
		ALGORITHM_API const std::string& getData( const std::string& identifier );
		ALGORITHM_API void setData( const std::string& identifier, const std::string& data );
	};
}
