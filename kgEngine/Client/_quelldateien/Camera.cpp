#include "../Camera/Camera.h"

namespace kg
{
	void Camera::init( const sf::Vector2u finalSize )
	{
		m_finalSize = sf::Vector2i( finalSize );
		m_View.setCenter( NULL, NULL );
		m_View.setSize( sf::Vector2f( finalSize ) );
	}

	bool Camera::setCenter( const sf::Vector2i position )
	{
// 		if( !m_focused )
// 		{
			this->m_View.setCenter( sf::Vector2f( position ) );
			return true;
// 		}
// 		else
// 			return false;
	}
	void Camera::moveCenter( const sf::Vector2i offset )
	{
		setCenter( sf::Vector2i( getCenter().x+offset.x, getCenter().y+offset.y ) );
	}
	bool Camera::setRotation( const float rotationInDegree )
	{
// 		if( !m_focusRotation )
// 		{
			this->m_View.setRotation( rotationInDegree );
			return true;
// 		}
// 		else
// 			return false;
	}
	void Camera::zoom( const float zoomFactor )
	{
		this->m_View.zoom( zoomFactor );
	}
	void Camera::setZoom( float zoom )
	{
		m_View.zoom( (m_finalSize.x / m_View.getSize().x) / zoom );
	}
	float Camera::getZoom()const
	{
		return m_finalSize.x / m_View.getSize().x;
		return 0;
	}
// 	bool cCamera::isFocused()const
// 	{
// 		return m_focused != nullptr;
// 	}
// 	bool cCamera::isRotationFocused()const
// 	{
// 		return m_focusRotation;
// 	}
// 	void cCamera::focus( cFocusable& toFocus, const bool focusRotation )
// 	{
// 		this->m_focused = &toFocus;
// 		this->m_focusRotation = focusRotation;
// 	}
// 	void cCamera::free()
// 	{
// 		this->m_focused = nullptr;
// 		this->m_focusRotation = false;
// 	}
	void Camera::draw( sf::Sprite& toDraw, int zValue )
	{
		this->m_spritesToRender[zValue].push_back( &toDraw );
	}
	void Camera::draw( std::vector<sf::Sprite*>& toDraw, int zValue )
	{
		std::vector<sf::Sprite*>& drawer = m_spritesToRender[zValue];
		for( auto& el : toDraw )
			drawer.push_back( el );
	}
	void Camera::display( sf::RenderTarget& renderTarget )
	{
		//wenn ein objekt fokussiert wird: m_View anpassen
// 		if( m_focused )
// 		{
// 			m_View.setCenter( sf::Vector2f( m_focused->getPosition() ) );
// 			if( m_focusRotation )
// 				m_View.setRotation( m_focused->getRotation() );
// 		}

		renderTarget.setView( m_View );

		for( const auto& el : m_spritesToRender )
			for( const auto& sprite : el.second )
				renderTarget.draw( *sprite );

		renderTarget.getDefaultView();

		m_spritesToRender.clear();
	}
	sf::Vector2i Camera::getFinalSize()const
	{
		return m_finalSize;
	}
	sf::FloatRect Camera::getCameraRect()const
	{
		return sf::FloatRect( getCenter().x - m_View.getSize().x / 2,
							  getCenter().y - m_View.getSize().y / 2,
							  m_View.getSize().x,
							  m_View.getSize().y );
	}
	sf::Vector2i Camera::getCenter()const
	{
		return sf::Vector2i( m_View.getCenter() );
	}
}