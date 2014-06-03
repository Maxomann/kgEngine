//_______NETWORK_INPUT_HANDLER_H_______//

#pragma once
#include"stdafx.h"
#include"cWorld.h"
#include"NetworkStringManager.h"
#include"SyncTime.h"

namespace kg
{
	ABSTRACT class NetworkInputHandler
	{
	public:
		virtual ~NetworkInputHandler()
		{ };

		//returns new gameStae if one should be set
		//else return nullptr
		virtual void handleInputFromServerToClient( const std::string& tag,
													const std::vector<std::string>& content,
													cWorld& world,
													SyncTime& syncTime ) = 0;

		virtual void handleInputFromClientToServer() = 0;
	};

	class StandartNetworkInputHandler : public NetworkInputHandler
	{
	public:
		void handleInputFromServerToClient( const std::string& tag,
											const std::vector<std::string>& content,
											cWorld& world,
											SyncTime& syncTime )
		{
			if( content.size() == NULL )
				throw std::exception( "handleInputFromServerToClient: content.size()==NULL" );

			if( tag == SyncTime::NetworkTag_Time )
			{
				syncTime.setTime( atoi( content.at( NULL ).c_str() ) );
			}
			else if( tag == SyncTime::NetworkTag_Ratio )
			{
				syncTime.setIngameToRealTimeRatio( static_cast< float >(std::atof( content.at( 0 ).c_str() )) );
			}
		}

		void handleInputFromClientToServer()
		{
			//empty
		}
	};
}