//_______CHUNK_LAYER_CPP_______//

#pragma once
#include "cChunkLayer.h"

namespace kg
{
	cChunkLayer::cChunkLayer( cCamera& camera, PluginManagement& pluginManagement, SyncTime& syncTime, NetworkStringManager& networkStringManager )
		: r_camera( &camera ),
		r_pluginManagement( &pluginManagement ),
		r_networkStringManager( &networkStringManager ),
		r_syncTime( &syncTime )
	{ }
	cChunkLayer::~cChunkLayer()
	{
		for( auto& x : m_chunks )
			for( auto& y : x.second )
				delete y.second;
	}
	cChunk* cChunkLayer::getChunk( const sf::Vector2i& positionInChunks )
	{
		for( auto& mp : m_chunks )
			if( mp.first == positionInChunks.x )
			{
				for( auto& chunk : mp.second )
					if( chunk.first == positionInChunks.y )
						return chunk.second;
				break;
			}

		return nullptr;
	}
	void cChunkLayer::initChunk( const sf::Vector2i& positionInChunks )
	{
		auto chunk = getChunk( positionInChunks );

		if( chunk == nullptr )
		{
			m_chunks[positionInChunks.x].insert( std::make_pair( positionInChunks.y, new cChunk(
				positionInChunks,
				*r_camera,
				*r_pluginManagement,
				*r_syncTime,
				*r_networkStringManager ) ) );
		}
	}
	void cChunkLayer::setActiveArea( const sf::IntRect& rectangle )
	{
		//TODO: addRawChunksInRectangle()???
#pragma message("warning: ChunkLayer::setActiveArea() is not implemented")
	}
	void cChunkLayer::reset()
	{
		throw("Not ready");
	}
	void cChunkLayer::update()
	{
		for( auto chIt = m_chunks.begin(); chIt != m_chunks.end(); ++chIt )
			for( auto it = chIt->second.begin(); it != chIt->second.end(); ++it )
				it->second->update();
	}
	void cChunkLayer::draw()
	{
		for( auto chIt = m_chunks.begin(); chIt != m_chunks.end(); ++chIt )
			for( auto it = chIt->second.begin(); it != chIt->second.end(); ++it )
				it->second->draw();
	}
}