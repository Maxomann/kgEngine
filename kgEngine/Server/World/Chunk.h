//_______CHUNK_______//

#pragma once
#include "../stdafx.h"

namespace kg
{
	class Chunk
	{
		typedef std::array< std::array<int, chunkSizeInTiles>, chunkSizeInTiles > FieldContainer;
		std::array< std::array<int, chunkSizeInTiles>, chunkSizeInTiles > m_fields;

	public:
		Chunk();

		void setField( const sf::Vector2i relativeTilePosition, int id );

		int getField( const sf::Vector2i position )const;

		const FieldContainer& getFieldData()const;
	};
}
