#include "../aFile.h"

ALGORITHM_API bool kg::aDataByIdentifierFile::loadFromFile( const std::string& path )
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
	return true;
}

ALGORITHM_API const std::string& kg::aDataByIdentifierFile::getData( const std::string& identifier )
{
	return m_data[identifier];
}

ALGORITHM_API void kg::aDataByIdentifierFile::saveToFile( const std::string& path )
{
	std::ofstream file;
	file.open( path, std::ios::trunc );
	if( !file.is_open() )
		REPORT_ERROR_FILEACCESS( "could not open/create file: " + path );

	file << toString();

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

ALGORITHM_API const std::map<std::string, std::string>& kg::aDataByIdentifierFile::getAllData()
{
	return m_data;
}

ALGORITHM_API std::string kg::aLoadFileToString( const std::string& path )
{
	std::string returnValue;

	std::ifstream file;
	file.open( path );
	if( !file.is_open() )
		REPORT_ERROR_FILEACCESS( "could not open file: " + path );

	std::string line;

	while( std::getline( file, line ) )
		returnValue += line;

	file.close();

	return returnValue;
}

ALGORITHM_API void kg::aSaveStringToFile( const std::string& path, const std::string& data )
{
	std::ofstream file;
	file.open( path, std::ios::trunc );
	if( !file.is_open() )
		REPORT_ERROR_FILEACCESS( "could not open file: " + path );

	file << data;
	file.close();
	return;
}

ALGORITHM_API char* kg::aLoadFileToCharPointer( const std::string& path )
{
	auto str = aLoadFileToString( path );

	char* file = new char[str.length() + 1];
	strcpy( file, str.c_str() );

	return file;
}