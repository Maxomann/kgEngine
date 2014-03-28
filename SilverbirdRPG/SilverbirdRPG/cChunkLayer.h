//_______CHUNK_LAYER_H_______//

#pragma once
#include"stdafx.h"
#include"cChunk.h"
#include"SyncTime.h"

namespace kg
{
	class cChunkLayer
	{
		////////Refs
		cCamera*						r_camera;
		PluginManagement*				r_pluginManagement;
		NetworkStringManager*			r_networkStringManager;
		SyncTime*						r_syncTime;

		//x=first int; y=second int;
#pragma message("warning: cChunkLayer change to sf::vector2i")
		std::map<int, std::map<int, cChunk*> >	m_chunks;

	public:
		cChunkLayer( cCamera& camera, PluginManagement& pluginManagement, SyncTime& syncTime, NetworkStringManager& networkStringManager );
		~cChunkLayer();

		//returns nullptr if chunk is not loaded
		cChunk*	getChunk( const sf::Vector2i& positionInChunks );

		//if chunk is already loaded, it calls
		//	Chunk::loadFromString(chunkData);
		void initChunk( const sf::Vector2i& positionInChunks );

		//requests Chunk data from server, where no chunks are loaded
		//deletes Chunks outside this area
		//rect in Pixel
		void	setActiveArea( const sf::IntRect& rectangle );

		//Deletes EVRYTHING on this layer so it has to be reloaded from the server
		void	reset();

		void	update();

		void	draw();
	};
}
