#include "../aDataByIdentifierFile.h"

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

	return false;
}

ALGORITHM_API const std::string& kg::aDataByIdentifierFile::getData( const std::string identifier ) const
{
	return m_data.at( identifier );
}

ALGORITHM_API bool kg::aDataByIdentifierFile::writeToFile( const std::string& path )
{
	REPORT_ERROR_NOT_IMPLEMENTED;
}

ALGORITHM_API std::string kg::aDataByIdentifierFile::toString() const
{
	REPORT_ERROR_NOT_IMPLEMENTED;
}

ALGORITHM_API void kg::aDataByIdentifierFile::setData( const std::string& identifier, const std::string& data )
{
	REPORT_ERROR_NOT_IMPLEMENTED;
}