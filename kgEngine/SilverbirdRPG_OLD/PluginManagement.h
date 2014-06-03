//_______PLUGIN_MANAGEMENT_H_______//
#pragma once
#include"stdafx.h"
#include"cFieldFactory.h"

namespace kg
{
	class PluginManagement
	{
	private:
		ResourceManagement*								r_resourceManagement;

		//to scale all objects to the same relation
		int												m_biggestTileSize;

		std::unordered_map<int, cFieldFactory>			m_cFieldFactorys;

	public:
		PluginManagement( ResourceManagement& resourceManagement );

		//ALLOCATES NEW MEMORY!
		//If field is not loaded, function returns nullptr
		cField*	getClientField( const int id, const sf::Vector2i& positionInTiles );

		//In Pixel
		int				getSizeOfTile()const;
	};
}
