//_______CONFIG_FILE_______//

#pragma once
#include "stdafx.h"
#include "aException.h"

namespace kg
{
	class aDataByIdentifierFile
	{
		std::map<std::string, std::string> m_data;

	public:

		ALGORITHM_API void loadFromFile( const std::string& path );

		ALGORITHM_API void writeToFile( const std::string& path );
		ALGORITHM_API std::string toString()const;

		ALGORITHM_API const std::string& getData( const std::string identifier )const;
		ALGORITHM_API void setData( const std::string& identifier, const std::string& data );
	};

}
