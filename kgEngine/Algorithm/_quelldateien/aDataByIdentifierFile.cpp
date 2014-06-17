#include "../aDataByIdentifierFile.h"

ALGORITHM_API void kg::aDataByIdentifierFile::loadFromFile( const std::string& path )
{
	std::ifstream file;
	file.open( path );
	if( !file.is_open() )
		REPORT_ERROR_FILEACCESS( "could not open file: " + path );

	std::string line;

	while( std::getline( file, line ) )
	{
		std::string identifier;
		bool afterBreak = false; //afer ':'
		for( const auto& el : line )
		{
			if( afterBreak )
				m_data[identifier].push_back( el );
			else if( el == ':' )
				afterBreak = true;
			else
				identifier.push_back( el );
		}
	}

	file.close();
}

ALGORITHM_API const std::string& kg::aDataByIdentifierFile::getData( const std::string& identifier )
{
	return m_data[ identifier ];
}

ALGORITHM_API void kg::aDataByIdentifierFile::writeToFile( const std::string& path )
{
	std::ofstream file;
	file.open( path, std::ios_base::binary || std::ios_base::out );
	if( !file.is_open() )
		REPORT_ERROR_FILEACCESS( "could not open/create file: " + path );
	
	for( const auto& el : m_data )
		file << el.first << ":" << el.second << "\n";

	file.close();
}

ALGORITHM_API std::string kg::aDataByIdentifierFile::toString() const
{
	std::string str;
	for( const auto& el : m_data )
	{
		str += el.first;
		str += ":";
		str += el.second;
		str += "\n";
	}
	return str;
}

ALGORITHM_API void kg::aDataByIdentifierFile::setData( const std::string& identifier, const std::string& data )
{
	m_data[identifier] = data;
}
