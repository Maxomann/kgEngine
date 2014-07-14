#pragma once
#include "../stdafx.h"

namespace kg
{
	struct AnimationSettings
	{
		sf::Vector2i frameSize = { -1, -1 };

		//A.size()=stateCount; B.size()=frames; B.at(x)=frameTime;
		std::vector<std::vector<int>> frameInfo;

		sf::Vector2i offset = { 0, 0 };

		//every element in the Vector is a state (Y-Coordinate). Give the amount of frames (X-Coordinate).
		//loadFromFile: xml-file
		AnimationSettings();

		virtual bool loadFromFile( const std::string& path );
		virtual bool saveToFile( const std::string path )const;

		bool isStateAvailable( unsigned int stateId ) const;
		bool isFrameAvailable( unsigned int stateId, unsigned int frameId ) const;

		const char* FRAME_SIZE_X = "frameSizeX";
		const char* FRAME_SIZE_Y = "frameSizeY";
		const char* OFFSET_X = "offsetX";
		const char* OFFSET_Y = "offsetY";

		const char* STATE = "animationState";
		const char* TIME = "time";
		const char* FRAME = "frame";
	};
}
