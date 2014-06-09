//_______FIELD_FACTORY_H_______//
#pragma once
#include"stdafx.h"
#include"Factory.h"
#include"cField.h"
#include"aString.h"

namespace kg
{
	class cFieldFactory : public Factory<cField>
	{
	private:
		//relative to resource folder
		std::string		m_pathOfTexture;

		sf::Vector2i	m_positionOnTexture;
		int				m_sizeInPixel;
		int				m_finalSizeInPixel;

		std::string		m_name;

	protected:

		void			Factory<cField>::m_loadFromFile( const std::string& path );

	public:
		cFieldFactory( const std::string& path, ResourceManagement& resourceManagement );

		cField*			getField( const sf::Vector2i& postionInTiles );

		void			setFinalSizeInPixel( const int size );

		int				getSizeInPixel()const;
		std::string		getName()const;

		//File extension
		//.cField
		//FieldFactory can be loaded from for example:
		//	"./MyField.cField"
		static const std::string FILE_EXTENSION;
	};
}
