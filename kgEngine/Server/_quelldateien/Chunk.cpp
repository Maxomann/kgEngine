#include "../World/Chunk.h"

namespace kg
{
	Chunk::Chunk()
	{
		//standart initialize fields
		for( int x = 0; x < chunkSizeInTiles; ++x )
			for( int y = 0; y < chunkSizeInTiles; ++y )
				m_fields[std::make_pair( x, y )] = NULL;
	}

	void Chunk::setField( const sf::Vector2i relativeTilePosition, int id )
{
		m_fields[std::make_pair( relativeTilePosition.x, relativeTilePosition.y )] = id;
	}

	int Chunk::getField( const sf::Vector2i position )const
	{
		return m_fields.at( std::make_pair( position.x, position.y ) );
	}

	const std::map< std::pair<int, int>, int >& Chunk::getFieldData() const
	{
		return m_fields;
	}
}
