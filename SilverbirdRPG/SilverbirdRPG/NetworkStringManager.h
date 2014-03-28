//_______NETWORK_STRING_MANAGER_H_______//

#pragma once
#include"stdafx.h"
#include"aString.h"
#include"nMessageServer.h"

namespace kg
{
	class NetworkStringManager
	{
	private:
		typedef std::unordered_map< std::string, std::unordered_map< std::string, std::vector< std::string > > > TagContainer;

		////Refs
		nMessageServer*												r_messageServer;

		TagContainer												m_sectionsRecieved;
		TagContainer												m_sectionsToSend;
		std::unordered_map< std::string, std::vector<std::string> > m_sectionsToBroadcast;

		std::unordered_map< std::string, bool >						m_hasNewString;

		const std::string			m_getStringToSend( const kg::nNetworkIdentification& nId );
		void						m_updateString( const kg::nNetworkIdentification& nId, const std::string& recievedString );

	public:
		NetworkStringManager( nMessageServer& messageServer );

		void						recieve();

		//sends messages
		void						update( const std::vector<nNetworkIdentification>& sendTo );
		void						update( const nNetworkIdentification& sendTo );

		void						addContentToTag( const kg::nNetworkIdentification& nId, const std::string& tag, const std::string& content );

		//content entered here will be sent to every unit in the Network
		//ATTENTION: it doesn't matter if you set broadcast to true or false
		//			 since it is just to make a difference between the
		//			 broadcast and non broadcast addContentToTag()
		void						addContentToTag( bool broadcast, const std::string& tag, const std::string& content );

		bool						hasNewString( const kg::nNetworkIdentification& nId );

		std::unordered_map<std::string, std::vector<std::string> >& getAllContentByNId( const nNetworkIdentification& nId );
		std::vector< std::string >	getContentByTag( const kg::nNetworkIdentification& nId, const std::string& tag );

		static const char			TAG_CHAR = '#';
		static const char			DIVISION_CHAR = '$';
		static const std::string	NETWORK_KEY;
	};
}
