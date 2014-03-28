//_______SYNCH_TIME_H_______//

#pragma once
#include"stdafx.h"
#include"NetworkStringManager.h"

namespace kg
{
	class SyncTime
	{
	private:
		////Refs
		kg::NetworkStringManager* r_NetworkStringManager;

		kg::nNetworkIdentification r_ServerNId;

		////

		int			m_time = 0;
		sf::Time	m_elapsedTime;
		float		m_ingameToRealTimeRatio = 1.0f;

		sf::Clock	m_clock;

		//counts time until resending time information
		sf::Clock	m_compareCounter;

		//If true this class will send its time to all users in the network
		bool		m_isMaster;

	public:
		//bool m_isMaster == true
		SyncTime( NetworkStringManager& NetworkStringManager );

		//bool m_isMaster == false
		SyncTime( NetworkStringManager& NetworkStringManager, kg::nNetworkIdentification ServerNId );

		const sf::Time	getTime()const;
		const sf::Time	getElapsedTime()const;
		float			getIngameToRealTimeRatio()const;

		//returns false if m_isMaster == false (ratio us sate anyways)
		bool			setIngameToRealTimeRatio( const float ratio );

		//returns false if m_isMaster == false (time will not be submitted)
		bool			submitTimeToNetwork()const;

		void			update();

		//returns false if m_isMaster == false (time will not be submitted)
		bool			setTime( const int time );

		static const std::string NetworkTag_Time;
		static const std::string NetworkTag_Ratio;
	};
}
