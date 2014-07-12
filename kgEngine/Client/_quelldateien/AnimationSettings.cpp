#include "../Settings/AnimationSettings.h"

using namespace rapidxml;

namespace kg
{
	AnimationSettings::AnimationSettings()
	{
	}

	bool AnimationSettings::loadFromFile( const std::string& path )
	{
		auto file = aLoadFileToCharPointer( path );

		xml_document<> doc;
		doc.parse<0>( file );

		//load information from parsed file
		auto frameSizeX = doc.first_node( FRAME_SIZE_X );
		frameSize.x = atoi( frameSizeX->value() );
		auto frameSizeY = doc.first_node( FRAME_SIZE_Y );
		frameSize.y = atoi( frameSizeY->value() );

		auto offsetX = doc.first_node( OFFSET_X );
		if( offsetX )
			offset.x = atoi( offsetX->value() );
		auto offsetY = doc.first_node( OFFSET_Y );
		if( offsetY )
			offset.y = atoi( offsetX->value() );

		auto stateTopNode = doc.first_node( STATE );
		for( auto stateSubNode = stateTopNode->first_node();
			 stateSubNode;
			 stateSubNode = stateSubNode->next_sibling() )
		{
			std::vector<int> thisStatesInfo;
			auto time = stateSubNode->first_attribute( TIME );
			if( time )
			{
				int timeForEveryFrame = 0;
				//in milliseconds
				timeForEveryFrame = atoi( time->value() );
				auto frameCount = stateSubNode->first_attribute( FRAME );
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

	bool AnimationSettings::saveToFile( const std::string path )const
	{
		//doc does not need to be loaded before modifying because AnimationSettings does not inherit
		xml_document<> doc;

		//save Information

		//FrameSize
		doc.append_node( doc.allocate_node( node_element, FRAME_SIZE_X, doc.allocate_string( std::to_string( frameSize.x ).c_str() ) ) );
		doc.append_node( doc.allocate_node( node_element, FRAME_SIZE_Y, doc.allocate_string( std::to_string( frameSize.y ).c_str() ) ) );

		//Offset
		doc.append_node( doc.allocate_node( node_element, OFFSET_X, doc.allocate_string( std::to_string( offset.x ).c_str() ) ) );
		doc.append_node( doc.allocate_node( node_element, OFFSET_Y, doc.allocate_string( std::to_string( offset.y ).c_str() ) ) );

		auto stateSignalNode = doc.allocate_node( node_element, STATE );
		doc.append_node( stateSignalNode );

		for( int state = 0; state < frameInfo.size(); ++state )
		{
			auto stateNode = doc.allocate_node( node_element, doc.allocate_string( std::to_string( state ).c_str() ) );
			stateSignalNode->append_node( stateNode );

			for( int frame = 0; frame < frameInfo.at( state ).size(); ++frame )
			{
				auto frameNode = doc.allocate_node( node_element,
													doc.allocate_string( std::to_string( frame ).c_str() ),
													doc.allocate_string( std::to_string( frameInfo.at( state ).at( frame ) ).c_str() ) );
				stateNode->append_node( frameNode );
			}
		}

		std::stringstream s;
		s << doc;
		aSaveStringToFile( path, s.str() );

		return true;
	}
}