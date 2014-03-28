#include "NetworkStringManager.h"

const std::string kg::NetworkStringManager::NETWORK_KEY = "NSM";

kg::NetworkStringManager::NetworkStringManager( nMessageServer& messageServer )
: r_messageServer( &messageServer )
{
	for( auto& el : m_hasNewString )
		el.second = false;
};

void kg::NetworkStringManager::recieve()
{
	auto recievedMes = r_messageServer->getRecievedMessages( NETWORK_KEY );
	for( const auto&el : recievedMes )
		m_updateString( el.first, el.second );
}

void kg::NetworkStringManager::update( const nNetworkIdentification& sendTo )
{
	std::vector<nNetworkIdentification>vec;
	vec.push_back( sendTo );
	this->update( vec );
}

void kg::NetworkStringManager::update( const std::vector<nNetworkIdentification>& sendTo )
{
	for( const auto& el : sendTo )
	{
		std::string toSend = m_getStringToSend( el );
		if( toSend != "" )
		{
			r_messageServer->send( std::make_pair( NETWORK_KEY, toSend ), el );
		}
	}

	this->m_sectionsRecieved.clear();
	this->m_sectionsToSend.clear();
	this->m_sectionsToBroadcast.clear();

	for( auto& el : m_hasNewString )
		el.second = false;
};

std::unordered_map<std::string, std::vector<std::string> >& kg::NetworkStringManager::getAllContentByNId( const nNetworkIdentification& nId )
{
	return m_sectionsRecieved[nId.toString()];
}

std::vector< std::string > kg::NetworkStringManager::getContentByTag( const kg::nNetworkIdentification& nId, const std::string& tag )
{
	return m_sectionsRecieved[nId.toString()][tag];
};

void kg::NetworkStringManager::addContentToTag( const kg::nNetworkIdentification& nId, const std::string& tag, const std::string& content )
{
	this->m_sectionsToSend[nId.toString()][tag].push_back( content );
};

void kg::NetworkStringManager::addContentToTag( bool broadcast, const std::string& tag, const std::string& content )
{
	this->m_sectionsToBroadcast[tag].push_back( content );
};

bool kg::NetworkStringManager::hasNewString( const kg::nNetworkIdentification& nId )
{
	return m_hasNewString[nId.toString()];
};

const std::string kg::NetworkStringManager::m_getStringToSend( const kg::nNetworkIdentification& nId )
{
	//Contents aus Broadcast hinzufügen
	for( const auto&tag : m_sectionsToBroadcast )
		for( const auto&con : tag.second )
			this->addContentToTag( nId, tag.first, con );

	std::string returnValue( "" );

	for( const auto &el : m_sectionsToSend[nId.toString()] )
	{
		returnValue += el.first;
		returnValue += DIVISION_CHAR;

		for( const auto&str : el.second )
		{
			returnValue += str;
			returnValue += DIVISION_CHAR;
		}
		returnValue.push_back( TAG_CHAR );
	}

	if( returnValue.size() > NULL )
		returnValue.pop_back();

	return returnValue;
};

void kg::NetworkStringManager::m_updateString( const kg::nNetworkIdentification& nId, const std::string& recievedString )
{
	auto tagRegions = kg::aSplitString::function( recievedString, DIVISION_CHAR, kg::aSplitString::operation::REMOVE );
	if( tagRegions.size() <= NULL )
		return;
	std::string tag = tagRegions.at( 0 );

	for( unsigned int a = 1; a < tagRegions.size(); ++a )
	{
		if( tagRegions.at( a ).at( 0 ) == TAG_CHAR )
		{
			tag = tagRegions.at( a );
			tag.erase( tag.begin() );
		}
		else
		{
			m_sectionsRecieved[nId.toString()][tag].push_back( tagRegions.at( a ) );
		}
	}

	this->m_hasNewString[nId.toString()] = true;
};