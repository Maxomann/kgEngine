//_______ANIMATION_______//

#pragma once
#include "../stdafx.h"

namespace kg
{
	struct AnimationSettings
	{
		sf::Vector2i frameSize;

		//A.size()=stateCount; B.size()=frames; B.at(x)=frameTime;
		std::vector<std::vector<int>> frameInfo;


		//every element in the Vector is a state (Y-Coordinate). Give the amount of frames (X-Coordinate).
		AnimationSettings( const sf::Vector2i& frameSize, const std::vector<std::vector<int>>& frameInfo );
		//loadFromFile: xml-file
		AnimationSettings( const std::string& path );

		bool isStateAvailable( unsigned int stateId ) const;
		bool isFrameAvailable( unsigned int stateId, unsigned int frameId ) const;

		static const int MAX_FILE_SIZE = 16384;

	};

	class Animation
	{
		const AnimationSettings m_settings;

		unsigned int m_frame = 0;
		unsigned int m_state = 0;

		bool m_run;

		sf::Clock m_timeInFrame;

	public:
		//Animation starts by default
		Animation( const AnimationSettings& settings, bool start = true );

		void run();
		void stop();
		void reset( bool resetState = false );

		//returns false if frame not available
		bool setFrame( int id );
		//returns false if state not available
		bool setState( int id );

		void apply( sf::Sprite& toSprite );

		void frame();

		const AnimationSettings& getSettings()const;
	};

	typedef std::map<int, Animation> AnimationByIdMap;
}