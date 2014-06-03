//_______CHUNK_LAYER_H_______//
#pragma once
#include"stdafx.h"
#include"SyncTime.h"
#include"PluginManagement.h"
#include"sChunk.h"

namespace kg
{
	class sChunkLayer
	{
		PluginManagement*				r_pluginManagement;
		NetworkStringManager*			r_networkStringManager;
		SyncTime*						r_syncTime;

		//std::pair<x,y> replaces sf::vector2i(x,y)
		std::map<std::pair<int, int>, sChunk*>	m_chunks;

	public:
		sChunkLayer( PluginManagement& pluginManagement, SyncTime& syncTime, NetworkStringManager& networkStringManager );
		~sChunkLayer();

		sChunk& getChunk( const sf::Vector2i position );

		//Give sf::IntRect in Chunks!
		void setActiveAreas( const std::vector<sf::IntRect> areas );

		void update();
	};
}
