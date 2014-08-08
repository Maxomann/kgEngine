#include "../World/Chunk.h"

namespace kg
{
	Chunk::Chunk()
	{
		//default initialize fields
		for( int x = 0; x < chunkSizeInTiles; ++x )
			for( int y = 0; y < chunkSizeInTiles; ++y )
				m_fields[x][y] = 0;
	}

	void Chunk::setField( const sf::Vector2i relativeTilePosition, int id )
{
		m_fields[relativeTilePosition.x][relativeTilePosition.y] = id;
	}

	int Chunk::getField( const sf::Vector2i position )const
	{
		return m_fields[position.x][position.y];
	}

	const Chunk::FieldContainer& Chunk::getFieldData() const
	{
		return m_fields;
	}
}
