//_______CHUNK_______//

#pragma once
#include "../stdafx.h"

namespace kg
{
	class Chunk
	{
		std::map< std::pair<int,int>, int > m_fields;

	public:
		Chunk();

		void setField( const sf::Vector2i position, int id );

		int getField( const sf::Vector2i position );

		static const sf::Vector2i size;

		const std::map< std::pair<int, int>, int >& getFieldData()const;
	};
}
