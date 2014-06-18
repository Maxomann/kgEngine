#include "../World/Chunk.h"

namespace kg
{

	Chunk::Chunk()
	{
		//standart initialize fields
		for( int x = 0; x < chunkSizeInTiles; ++x )
			for( int y = 0; y < chunkSizeInTiles; ++y )
				m_fields[std::make_pair( x, y )] = 1;
	}

	void Chunk::setField( const sf::Vector2i position, int id )
	{
		m_fields[std::make_pair( position.x, position.y )] = id;
	}

	int Chunk::getField( const sf::Vector2i position )
	{
		return m_fields.at( std::make_pair( position.x, position.y ) );
	}

	const std::map< std::pair<int, int>, int >& Chunk::getFieldData() const
	{
		return m_fields;
	}

	std::string Chunk::nToString() const
	{
		
		std::string str;

		for( int x = 0; x < chunkSizeInTiles; ++x )
		{
			for( int y = 0; y < chunkSizeInTiles; ++y )
			{
				str += std::to_string(m_fields.at(std::make_pair( x, y )));
				str.push_back( standartSplitChar );
			}
		}

		return str;
	}


}
