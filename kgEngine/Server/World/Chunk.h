//_______CHUNK_______//

#pragma once
#include "../stdafx.h"

namespace kg
{
	class Chunk : public nNetworkSendable
	{
		std::map< std::pair<int,int>, int > m_fields;

	public:
		Chunk();

		void setField( const sf::Vector2i position, int id );

		int getField( const sf::Vector2i position );

		const std::map< std::pair<int, int>, int >& getFieldData()const;

		virtual std::string nToString() const;

	};
}
