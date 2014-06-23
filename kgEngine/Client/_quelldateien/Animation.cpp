#include "../Drawing/Animation.h"

using namespace rapidxml;

namespace kg
{

	AnimationSettings::AnimationSettings( const sf::Vector2i& frameSize, const std::vector<std::vector<int>>& frameInfo )
		:frameSize( frameSize ),
		frameInfo( frameInfo )
	{

	}

	AnimationSettings::AnimationSettings( const std::string& path )
	{
		auto str = aLoadFileToString( path );

		char file[MAX_FILE_SIZE];
		strncpy_s( file, str.c_str(), sizeof( file ) );
		file[sizeof( file ) - 1] = 0;

		xml_document<> doc;
		doc.parse<0>( file );

		//load information from parsed file
		auto frameSizeX = doc.first_node( "frameSizeX" );
		frameSize.x = atoi( frameSizeX->value() );
		auto frameSizeY = doc.first_node( "frameSizeY" );
		frameSize.y = atoi( frameSizeY->value() );

		auto stateTopNode = doc.first_node( "state" );
		for( auto stateSubNode = stateTopNode->first_node();
			 stateSubNode;
			 stateSubNode = stateSubNode->next_sibling() )
		{
			std::vector<int> thisStatesInfo;
			auto time = stateSubNode->first_attribute( "time" );
			if( time )
			{
				int timeForEveryFrame = 0;
				//in milliseconds
				timeForEveryFrame = atoi( time->value() );
				auto frameCount = stateSubNode->first_attribute( "frame" );
				if( frameCount )
				{
					for( int i = 0; i < atoi( frameCount->value() ); ++i )
						thisStatesInfo.push_back( timeForEveryFrame );
				}
				else
				{
					for( auto frameNode = stateSubNode->first_node();
						 frameNode;
						 frameNode = frameNode->next_sibling() )
					{
						if( atoi( frameNode->value() )==0 )
							thisStatesInfo.push_back( timeForEveryFrame );
						else
							thisStatesInfo.push_back( atoi( frameNode->value() ) );
					}
				}
			}
			else
			{
				for( auto frameNode = stateSubNode->first_node();
					 frameNode;
					 frameNode = frameNode->next_sibling() )
				{
					thisStatesInfo.push_back( atoi(frameNode->value()) );
				}
			}
			frameInfo.push_back( thisStatesInfo );
		}

	}

	bool AnimationSettings::isStateAvailable( unsigned int stateId ) const
	{
		if( stateId < frameInfo.size() )
			return true;
		else
			return false;
	}

	bool AnimationSettings::isFrameAvailable( unsigned int stateId, unsigned int frameId ) const
	{
		if( frameId < frameInfo.at( stateId ).size() )
			return true;
		else
			return false;
	}


	Animation::Animation( const AnimationSettings& settings, bool start )
		:m_settings( settings ),
		m_run( start )
	{

	}

	void Animation::run()
	{
		m_run = true;
	}

	void Animation::stop()
	{
		m_run = false;
	}

	void Animation::reset( bool resetState )
	{
		m_frame = 0;
		if( resetState )
			m_state = 0;
		m_timeInFrame.restart();
	}

	bool Animation::setFrame( int id )
	{
		if( m_settings.isFrameAvailable(m_state, m_frame) )
#ifdef _DEBUG
			REPORT_ERROR_GRAPHICS( "frame not available" );
#elif
			return false;
#endif
		m_frame = id;
		m_timeInFrame.restart();
		return true;
	}

	bool Animation::setState( int id )
	{
 		if( m_settings.isStateAvailable(id) )
#ifdef _DEBUG
			REPORT_ERROR_GRAPHICS( "state not available" );
#elif
			return false;
#endif
		m_state = id;
		m_frame = 0;
		m_timeInFrame.restart();
		return true;
	}

	void Animation::apply( sf::Sprite& toSprite )
	{
		toSprite.setTextureRect( sf::IntRect(
			m_settings.frameSize.x*m_frame,
			m_settings.frameSize.y*m_state,
			m_settings.frameSize.x,
			m_settings.frameSize.y
			) );
	}

	void Animation::frame()
	{
		if( m_run )
		{
			if( m_timeInFrame.getElapsedTime().asMilliseconds() > m_settings.frameInfo.at( m_state ).at( m_frame ) )
			{
				if( m_settings.isFrameAvailable( m_state, m_frame + 1 ) )
					m_frame++;
				else
					m_frame = 0;

				m_timeInFrame.restart();
			}
		}
	}

	const AnimationSettings& Animation::getSettings() const
	{
		return m_settings;
	}

}
