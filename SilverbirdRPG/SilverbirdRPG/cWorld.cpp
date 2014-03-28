//_______WORLD_CPP_______//

#pragma once
#include "cWorld.h"

namespace kg
{
	cWorld::cWorld( cCamera& camera, PluginManagement& pluginManagement, SyncTime& syncTime, NetworkStringManager& networkStringManager )
		: r_camera( &camera ),
		r_pluginManagement( &pluginManagement ),
		r_networkStringManager( &networkStringManager ),
		r_syncTime( &syncTime ),
		m_chunkLayer( camera, pluginManagement, syncTime, networkStringManager )
	{ }
	cChunkLayer* cWorld::getChunkLayer()
	{
		return &m_chunkLayer;
	}
	int cWorld::getChunkLayerId()const
	{
		return m_chunkLayerId;
	}
	void cWorld::setChunkLayerId( int layer )
	{
		this->m_chunkLayerId = layer;
		//TODO:submit to server
#pragma message("warning: World::setChunkLayerId() doesen't submit information to the server")
		m_chunkLayer.reset();
	}
	void cWorld::update()
	{
		this->m_chunkLayer.update();
	}
	void cWorld::draw()
	{
		this->m_chunkLayer.draw();
	}
}