#include "../World/Chunk.h"

namespace kg
{

	Chunk::Chunk()
	{
		//standart initialize fields
		for( int x = 0; x < size.x; ++x )
			for( int y = 0; y < size.x; ++y )
				m_fields[sf::Vector2i( x, y )] = 0;
	}

	const sf::Vector2i Chunk::size = sf::Vector2i( 19, 19 );

	void Chunk::setField( const sf::Vector2i position, int id )
	{
		m_fields[position] = id;
	}

	int Chunk::getField( const sf::Vector2i position )
	{
		return m_fields.at(position);
	}

	const std::map< sf::Vector2i, int >& Chunk::getFieldData() const
	{
		return m_fields;
	}


}
