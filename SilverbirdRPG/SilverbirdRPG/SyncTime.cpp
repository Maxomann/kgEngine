#include "SyncTime.h"

const std::string kg::SyncTime::NetworkTag_Time = std::string( "SyT" );
//Sync time: To submit the server time to clients

const std::string kg::SyncTime::NetworkTag_Ratio = std::string( "SyR" );
//Ratio: To submit the servers m_ingameToRealTimeRatio to clients

kg::SyncTime::SyncTime( kg::NetworkStringManager& NetworkStringManager )
: r_NetworkStringManager( &NetworkStringManager ), m_isMaster( true ), r_ServerNId( "", 0 )
{
	m_clock.restart();
	m_compareCounter.restart();
}

kg::SyncTime::SyncTime( NetworkStringManager& NetworkStringManager, kg::nNetworkIdentification ServerNId )
: r_NetworkStringManager( &NetworkStringManager ), m_isMaster( false ), r_ServerNId( ServerNId )
{
	m_clock.restart();
	m_compareCounter.restart();
}

const sf::Time kg::SyncTime::getTime()const
{
	return sf::milliseconds( m_time );
}

const sf::Time kg::SyncTime::getElapsedTime()const
{
	return m_elapsedTime;
}

float kg::SyncTime::getIngameToRealTimeRatio()const
{
	return m_ingameToRealTimeRatio;
}

bool kg::SyncTime::setIngameToRealTimeRatio( const float ratio )
{
	if( !this->m_isMaster )
	{
		this->m_ingameToRealTimeRatio = ratio;
		return false;
	}
	else
	{
		this->m_ingameToRealTimeRatio = ratio;
		this->submitTimeToNetwork();
		return true;
	}
};

bool kg::SyncTime::submitTimeToNetwork()const
{
	if( !m_isMaster )
		return false;
	r_NetworkStringManager->addContentToTag( true, NetworkTag_Time, std::to_string( m_time ) );
	r_NetworkStringManager->addContentToTag( true, NetworkTag_Ratio, std::to_string( m_ingameToRealTimeRatio ) );
	return true;
};

void kg::SyncTime::update()
{
	m_elapsedTime = sf::milliseconds( static_cast< sf::Int32 >(m_clock.getElapsedTime().asMilliseconds()*m_ingameToRealTimeRatio) );
	m_time += static_cast< int >(m_clock.getElapsedTime().asMilliseconds()*m_ingameToRealTimeRatio);
	//alle 24 stunden zeit zurück auf null setzen
	//damit Integer Größe nicht überschritten wird
	if( m_time >= 86400000 )
		m_time = 0;
	m_clock.restart();

	//alle 30 sekunden zeit mit clients abgleichen
	if( m_isMaster && m_compareCounter.getElapsedTime().asSeconds() > 30 )
	{
		this->submitTimeToNetwork();
		m_compareCounter.restart();
	}
}

bool kg::SyncTime::setTime( const int time )
{
	if( !this->m_isMaster )
	{
		this->m_time = time;
		return false;
	}
	else
	{
		this->m_time = time;
		this->submitTimeToNetwork();
		return true;
	}
}