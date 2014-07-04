#include "../Drawing/Animation.h"

namespace kg
{

	Animation::Animation( const AnimationSettings& settings, bool start )
		:m_settings( settings ),
		m_run( start )
	{ }

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
		if( m_settings.isFrameAvailable( m_state, m_frame ) )
#ifdef _DEBUG
			REPORT_ERROR_GRAPHICS( "frame not available" );
#else
			return false;
#endif
		m_frame = id;
		m_timeInFrame.restart();
		return true;
	}

	bool Animation::setState( int id )
	{
		if( m_settings.isStateAvailable( id ) )
#ifdef _DEBUG
			REPORT_ERROR_GRAPHICS( "state not available" );
#else
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
			m_settings.frameSize.x*m_frame + m_settings.offset.x,
			m_settings.frameSize.y*m_state + m_settings.offset.y,
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