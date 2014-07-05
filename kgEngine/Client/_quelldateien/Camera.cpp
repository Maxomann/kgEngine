#include "../Drawing/Camera.h"

namespace kg
{
	using namespace sf;

	//const float pi = 3.14159265;
	/*	const int MaxCapacity = 400000;*/
	const int MaxCapacity = 40000000;
	const int LookupSize = 512;

	float getSin[LookupSize];
	float getCos[LookupSize];
	bool initialized = false;

	void create_lookup()
	{
		for( int i = 0; i < LookupSize; i++ )
		{
			getSin[i] = sin( i * pi / LookupSize * 2 );
			getCos[i] = cos( i * pi / LookupSize * 2 );
		}
		initialized = true;
	}

	SpriteBatch::SpriteBatch( void ) : count( 0 ), capacity( 40 )
	{
		vertices.resize( capacity );

		if( !initialized )
			create_lookup();
	}

	SpriteBatch::~SpriteBatch( void )
	{ }

	void SpriteBatch::draw( const Sprite &sprite )
	{
		draw( sprite.getTexture(), sprite.getPosition(), sprite.getTextureRect(), sprite.getColor(), sprite.getScale(), sprite.getOrigin(), sprite.getRotation() );
	}

	void SpriteBatch::display( bool reset, bool flush )
	{
		rt->draw( &vertices[0], count * 4, PrimitiveType::Quads, state );
		if( flush ) count = 0;
		if( reset ) state = RenderStates();
	}

	int SpriteBatch::create( const Texture *texture )
	{
		if( texture != state.texture )
		{
			display( false );
			state.texture = texture;
		}

		if( count * 4 >= capacity )
		{
			//display(false);
			if( capacity < MaxCapacity )
			{
				capacity *= 2;
				if( capacity > MaxCapacity ) capacity = MaxCapacity;
				vertices.resize( capacity );
			}
		}
		return 4 * count++;
	}

	void SpriteBatch::draw(
		const Texture *texture, const Vector2f &position,
		const IntRect &rec, const Color &color, const Vector2f &scale,
		const Vector2f &origin, float rotation )
	{
		auto index = create( texture );

		int rot = static_cast< int >(rotation / 360 * LookupSize + 0.5) & (LookupSize - 1);
		float _sin = getSin[rot];
		float _cos = getCos[rot];

		//float _sin = sinf(rotation);
		//float _cos = cosf(rotation);

		auto scalex = rec.width * scale.x;
		auto scaley = rec.height * scale.y;

		Vertex *ptr = &vertices[index];

		auto pX = -origin.x * scale.x;
		auto pY = -origin.y * scale.y;

		ptr->position.x = pX * _cos - pY * _sin + position.x;
		ptr->position.y = pX * _sin + pY * _cos + position.y;
		ptr->texCoords.x = rec.left;
		ptr->texCoords.y = rec.top;
		ptr->color = color;
		ptr++;

		pX += scalex;
		ptr->position.x = pX * _cos - pY * _sin + position.x;
		ptr->position.y = pX * _sin + pY * _cos + position.y;
		ptr->texCoords.x = rec.left + rec.width;
		ptr->texCoords.y = rec.top;
		ptr->color = color;
		ptr++;

		pY += scaley;
		ptr->position.x = pX * _cos - pY * _sin + position.x;
		ptr->position.y = pX * _sin + pY * _cos + position.y;
		ptr->texCoords.x = rec.left + rec.width;
		ptr->texCoords.y = rec.top + rec.height;
		ptr->color = color;
		ptr++;

		pX -= scalex;
		ptr->position.x = pX * _cos - pY * _sin + position.x;
		ptr->position.y = pX * _sin + pY * _cos + position.y;
		ptr->texCoords.x = rec.left;
		ptr->texCoords.y = rec.top + rec.height;
		ptr->color = color;
	}

	void SpriteBatch::draw( const Texture *texture, const FloatRect &dest, const IntRect &rec, const Color &color )
	{
		draw( texture, Vector2f( dest.left, dest.top ), rec, color, Vector2f( 1, 1 ), Vector2f( 0, 0 ), 0 );
	}

	void SpriteBatch::flush()
	{
		count = 0;
	}

	void SpriteBatch::setRenderStates( const sf::RenderStates &states )
	{
		display( false );
		this->state = states;
	}

	void SpriteBatch::setRenderTarget( sf::RenderTarget &rt )
	{
		this->rt = &rt;
	}




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
		setCenter( sf::Vector2i( getCenter().x + offset.x, getCenter().y + offset.y ) );
	}
	void Camera::setRotation( const float rotationInDegree )
	{
		// 		if( !m_focusRotation )
		// 		{
		this->m_View.setRotation( rotationInDegree );
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

		m_spriteBatch.setRenderTarget( renderTarget );

		for( const auto& el : m_spritesToRender )
			for( const auto& sprite : el.second )
				m_spriteBatch.draw( *sprite );

		m_spriteBatch.display();

		renderTarget.setView( renderTarget.getDefaultView() );

		m_spritesToRender.clear();
	}
	sf::Vector2u Camera::getFinalSize() const
	{
		return sf::Vector2u( m_finalSize );
	}
// 	sf::FloatRect Camera::getCameraRectWithoutRotation()const
// 	{
// 		return sf::FloatRect( getCenter().x - m_View.getSize().x / 2,
// 							  getCenter().y - m_View.getSize().y / 2,
// 							  m_View.getSize().x,
// 							  m_View.getSize().y );
// 	}
	sf::Vector2i Camera::getCenter()const
	{
		return sf::Vector2i( m_View.getCenter() );
	}

// 	sf::Vector2i Camera::getUpperLeftCorner()const
// 	{
// 		return sf::Vector2i( getCameraRectWithoutRotation().left, getCameraRectWithoutRotation().top );
// 	}

	void Camera::rotate( const float rotationInDegree )
	{
		m_View.rotate( rotationInDegree );
	}

	float Camera::getRotation()const
	{
		return m_View.getRotation();
	}

	const sf::View& Camera::getView() const
	{
		return m_View;
	}

}
