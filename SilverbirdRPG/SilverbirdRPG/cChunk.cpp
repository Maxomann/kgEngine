//_______CHUNK_CPP_______//

#pragma once
#include "cChunk.h"

namespace kg
{
	//const std::string cChunk::STANDART_CHUNK_DATA = std::string( "0,0;0,0;0,1;0,0;0,2;0,0;0,3;0,0;0,4;0,0;0,5;0,0;0,6;0,0;0,7;0,0;0,8;0,0;0,9;0,0;0,10;0,0;0,11;0,0;0,12;0,0;0,13;0,0;0,14;0,0;0,15;0,0;0,16;0,0;0,17;0,0;0,18;0,0;0,19;0,0;1,0;0,0;1,1;0,0;1,2;0,0;1,3;0,0;1,4;0,0;1,5;0,0;1,6;0,0;1,7;0,0;1,8;0,0;1,9;0,0;1,10;0,0;1,11;0,0;1,12;0,0;1,13;0,0;1,14;0,0;1,15;0,0;1,16;0,0;1,17;0,0;1,18;0,0;1,19;0,0;2,0;0,0;2,1;0,0;2,2;0,0;2,3;0,0;2,4;0,0;2,5;0,0;2,6;0,0;2,7;0,0;2,8;0,0;2,9;0,0;2,10;0,0;2,11;0,0;2,12;0,0;2,13;0,0;2,14;0,0;2,15;0,0;2,16;0,0;2,17;0,0;2,18;0,0;2,19;0,0;3,0;0,0;3,1;0,0;3,2;0,0;3,3;0,0;3,4;0,0;3,5;0,0;3,6;0,0;3,7;0,0;3,8;0,0;3,9;0,0;3,10;0,0;3,11;0,0;3,12;0,0;3,13;0,0;3,14;0,0;3,15;0,0;3,16;0,0;3,17;0,0;3,18;0,0;3,19;0,0;4,0;0,0;4,1;0,0;4,2;0,0;4,3;0,0;4,4;0,0;4,5;0,0;4,6;0,0;4,7;0,0;4,8;0,0;4,9;0,0;4,10;0,0;4,11;0,0;4,12;0,0;4,13;0,0;4,14;0,0;4,15;0,0;4,16;0,0;4,17;0,0;4,18;0,0;4,19;0,0;5,0;0,0;5,1;0,0;5,2;0,0;5,3;0,0;5,4;0,0;5,5;0,0;5,6;0,0;5,7;0,0;5,8;0,0;5,9;0,0;5,10;0,0;5,11;0,0;5,12;0,0;5,13;0,0;5,14;0,0;5,15;0,0;5,16;0,0;5,17;0,0;5,18;0,0;5,19;0,0;6,0;0,0;6,1;0,0;6,2;0,0;6,3;0,0;6,4;0,0;6,5;0,0;6,6;0,0;6,7;0,0;6,8;0,0;6,9;0,0;6,10;0,0;6,11;0,0;6,12;0,0;6,13;0,0;6,14;0,0;6,15;0,0;6,16;0,0;6,17;0,0;6,18;0,0;6,19;0,0;7,0;0,0;7,1;0,0;7,2;0,0;7,3;0,0;7,4;0,0;7,5;0,0;7,6;0,0;7,7;0,0;7,8;0,0;7,9;0,0;7,10;0,0;7,11;0,0;7,12;0,0;7,13;0,0;7,14;0,0;7,15;0,0;7,16;0,0;7,17;0,0;7,18;0,0;7,19;0,0;8,0;0,0;8,1;0,0;8,2;0,0;8,3;0,0;8,4;0,0;8,5;0,0;8,6;0,0;8,7;0,0;8,8;0,0;8,9;0,0;8,10;0,0;8,11;0,0;8,12;0,0;8,13;0,0;8,14;0,0;8,15;0,0;8,16;0,0;8,17;0,0;8,18;0,0;8,19;0,0;9,0;0,0;9,1;0,0;9,2;0,0;9,3;0,0;9,4;0,0;9,5;0,0;9,6;0,0;9,7;0,0;9,8;0,0;9,9;0,0;9,10;0,0;9,11;0,0;9,12;0,0;9,13;0,0;9,14;0,0;9,15;0,0;9,16;0,0;9,17;0,0;9,18;0,0;9,19;0,0;10,0;0,0;10,1;0,0;10,2;0,0;10,3;0,0;10,4;0,0;10,5;0,0;10,6;0,0;10,7;0,0;10,8;0,0;10,9;0,0;10,10;0,0;10,11;0,0;10,12;0,0;10,13;0,0;10,14;0,0;10,15;0,0;10,16;0,0;10,17;0,0;10,18;0,0;10,19;0,0;11,0;0,0;11,1;0,0;11,2;0,0;11,3;0,0;11,4;0,0;11,5;0,0;11,6;0,0;11,7;0,0;11,8;0,0;11,9;0,0;11,10;0,0;11,11;0,0;11,12;0,0;11,13;0,0;11,14;0,0;11,15;0,0;11,16;0,0;11,17;0,0;11,18;0,0;11,19;0,0;12,0;0,0;12,1;0,0;12,2;0,0;12,3;0,0;12,4;0,0;12,5;0,0;12,6;0,0;12,7;0,0;12,8;0,0;12,9;0,0;12,10;0,0;12,11;0,0;12,12;0,0;12,13;0,0;12,14;0,0;12,15;0,0;12,16;0,0;12,17;0,0;12,18;0,0;12,19;0,0;13,0;0,0;13,1;0,0;13,2;0,0;13,3;0,0;13,4;0,0;13,5;0,0;13,6;0,0;13,7;0,0;13,8;0,0;13,9;0,0;13,10;0,0;13,11;0,0;13,12;0,0;13,13;0,0;13,14;0,0;13,15;0,0;13,16;0,0;13,17;0,0;13,18;0,0;13,19;0,0;14,0;0,0;14,1;0,0;14,2;0,0;14,3;0,0;14,4;0,0;14,5;0,0;14,6;0,0;14,7;0,0;14,8;0,0;14,9;0,0;14,10;0,0;14,11;0,0;14,12;0,0;14,13;0,0;14,14;0,0;14,15;0,0;14,16;0,0;14,17;0,0;14,18;0,0;14,19;0,0;15,0;0,0;15,1;0,0;15,2;0,0;15,3;0,0;15,4;0,0;15,5;0,0;15,6;0,0;15,7;0,0;15,8;0,0;15,9;0,0;15,10;0,0;15,11;0,0;15,12;0,0;15,13;0,0;15,14;0,0;15,15;0,0;15,16;0,0;15,17;0,0;15,18;0,0;15,19;0,0;16,0;0,0;16,1;0,0;16,2;0,0;16,3;0,0;16,4;0,0;16,5;0,0;16,6;0,0;16,7;0,0;16,8;0,0;16,9;0,0;16,10;0,0;16,11;0,0;16,12;0,0;16,13;0,0;16,14;0,0;16,15;0,0;16,16;0,0;16,17;0,0;16,18;0,0;16,19;0,0;17,0;0,0;17,1;0,0;17,2;0,0;17,3;0,0;17,4;0,0;17,5;0,0;17,6;0,0;17,7;0,0;17,8;0,0;17,9;0,0;17,10;0,0;17,11;0,0;17,12;0,0;17,13;0,0;17,14;0,0;17,15;0,0;17,16;0,0;17,17;0,0;17,18;0,0;17,19;0,0;18,0;0,0;18,1;0,0;18,2;0,0;18,3;0,0;18,4;0,0;18,5;0,0;18,6;0,0;18,7;0,0;18,8;0,0;18,9;0,0;18,10;0,0;18,11;0,0;18,12;0,0;18,13;0,0;18,14;0,0;18,15;0,0;18,16;0,0;18,17;0,0;18,18;0,0;18,19;0,0;19,0;0,0;19,1;0,0;19,2;0,0;19,3;0,0;19,4;0,0;19,5;0,0;19,6;0,0;19,7;0,0;19,8;0,0;19,9;0,0;19,10;0,0;19,11;0,0;19,12;0,0;19,13;0,0;19,14;0,0;19,15;0,0;19,16;0,0;19,17;0,0;19,18;0,0;19,19;0,0;" );

	cChunk::cChunk( const sf::Vector2i& positionInChunks,
					cCamera& camera,
					PluginManagement& pluginManagement,
					SyncTime& syncTime,
					NetworkStringManager& networkStringManager )
					:
					r_camera( &camera ),
					r_pluginManagement( &pluginManagement ),
					r_networkStringManager( &networkStringManager ),
					r_syncTime( &syncTime ),
					m_positionInChunks( positionInChunks )
	{
	}
	cChunk::~cChunk()
	{ }
	const sf::Vector2i cChunk::getPositionInChunks()const
	{
		return m_positionInChunks;
	}
	//void cChunk::loadFromString( const std::string& chunkData )
	//{
	//	auto cd = chunkData;//copy for non const

	//	//Alle Felder l�schen
	//	for( auto& a : m_fields )
	//		for( auto& b : a )
	//			for( auto& c : b )
	//				delete c.second;

	//	//Leerzeichen entfernen
	//	cd.erase( std::remove( cd.begin(), cd.end(), ' ' ), cd.end() );
	//	auto mainParts = aSplitString::function(
	//		chunkData,
	//		';',
	//		aSplitString::REMOVE );

	//	sf::Vector3i position;
	//	//Main Parts durchgehen
	//	for( auto it = mainParts.begin(); it != mainParts.end(); ++it )
	//	{
	//		auto underParts = aSplitString::function( *it,
	//												  ',',
	//												  aSplitString::REMOVE );
	//		position.x = atoi( underParts.at( NULL ).c_str() );
	//		position.y = atoi( underParts.at( 1 ).c_str() );

	//		//zu den einzelnen felderdaten wechseln
	//		++it;

	//		underParts = aSplitString::function( *it,
	//											 ',',
	//											 aSplitString::REMOVE );
	//		//felddaten lesen
	//		for( auto underIt = underParts.begin(); underIt != underParts.end(); ++underIt )
	//		{
	//			position.z = atoi( underIt->c_str() );
	//			++underIt;
	//			cField* field = r_pluginManagement->getClientField( atoi( underIt->c_str() ),
	//																sf::Vector2i( position.x + m_positionInChunks.x*SIZE_IN_FIELDS, position.y + m_positionInChunks.y*SIZE_IN_FIELDS ) );
	//			//Feld nicht geladen abfangen
	//			if( field == nullptr )
	//				field = r_pluginManagement->getClientField( NULL,
	//				sf::Vector2i( position.x + m_positionInChunks.x*SIZE_IN_FIELDS, position.y + m_positionInChunks.y*SIZE_IN_FIELDS ) );
	//			m_fields.at( position.x ).at( position.y )[position.z] = field;
	//		}

	//		//for schleife verlassen
	//		if( it == mainParts.end() )
	//			break;
	//	}
	//}
	void cChunk::update()
	{
	}
	void cChunk::draw()
	{
	}
}