#include "../World/Chunk.h"

namespace kg
{

	Chunk::Chunk()
	{
		//standart initialize fields
		for( int x = 0; x < size.x; ++x )
			for( int y = 0; y < size.x; ++y )
				m_fields[std::make_pair( x, y )] = 0;
	}

	const sf::Vector2i Chunk::size = sf::Vector2i( 19, 19 );

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


}
