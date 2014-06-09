//_______CHUNK_H_______//
#pragma once
#include"stdafx.h"
#include"PluginManagement.h"
#include"NetworkStringManager.h"
#include"SyncTime.h"

namespace kg
{
	class cChunk
	{
	private:
		////////Refs
		kg::cCamera*					r_camera;
		PluginManagement*				r_pluginManagement;
		NetworkStringManager*			r_networkStringManager;
		SyncTime*						r_syncTime;

		const sf::Vector2i				m_positionInChunks;

	public:
		cChunk( const sf::Vector2i& positionInChunks,
				cCamera& camera,
				PluginManagement& pluginManagement,
				SyncTime& syncTime,
				NetworkStringManager& networkStringManager );
		~cChunk();

		const sf::Vector2i	getPositionInChunks()const;

		void update();

		void draw();

		static const int SIZE_IN_TILES = 20;
	};
}
