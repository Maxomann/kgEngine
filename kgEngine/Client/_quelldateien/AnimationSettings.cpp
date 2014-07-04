#include "../Settings/AnimationSettings.h"

using namespace rapidxml;

namespace kg
{
	AnimationSettings::AnimationSettings()
	{

	}

	bool AnimationSettings::loadFromFile( const std::string& path )
	{
		auto str = aLoadFileToString( path );

		// 		char file[MAX_FILE_SIZE];
		// 		strncpy_s( file, str.c_str(), sizeof( file ) );
		// 		file[sizeof( file ) - 1] = 0;

		char* file = new char[str.length() + 1];
		strcpy( file, str.c_str() );

		xml_document<> doc;
		doc.parse<0>( file );

		//load information from parsed file
		auto frameSizeX = doc.first_node( "frameSizeX" );
		frameSize.x = atoi( frameSizeX->value() );
		auto frameSizeY = doc.first_node( "frameSizeY" );
		frameSize.y = atoi( frameSizeY->value() );


		auto offsetX = doc.first_node( "offsetX" );
		if( offsetX )
			offset.x = atoi( offsetX->value() );
		auto offsetY = doc.first_node( "offsetY" );
		if( offsetY )
			offset.y = atoi( offsetX->value() );


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
						if( atoi( frameNode->value() ) == 0 )
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
					thisStatesInfo.push_back( atoi( frameNode->value() ) );
				}
			}
			frameInfo.push_back( thisStatesInfo );
		}


		delete[] file;
		return true;
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
}
