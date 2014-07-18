//_______RESOURCE_USER_______//

// #pragma once
// #include "stdafx.h"
// #include "ClientDatabase.h"
// 
// namespace kg
// {
// 	class ResourceUser : public aCallbackReciever
// 	{
// 
// 	};
// 
// 	class TileResourceUser : public ResourceUser
// 	{
// 	protected:
// 		virtual void onTilesModiefied( int callbackID, ClientDatabase& clientDatabase ) = 0;
// 
// 		TileResourceUser( ClientDatabase& clientDatabase );
// 
// 		virtual void onRegisterResourceCallbacks( ClientDatabase& clientDatabase );
// 
// 	};
// 
// 	class ConfigFileUser : public ResourceUser
// 	{
// 	protected:
// 		virtual void onResourceFileModified( int callbackID, ClientDatabase& clientDatabase ) = 0;
// 
// 		ConfigFileUser( ClientDatabase& clientDatabase );
// 
// 		virtual void onRegisterResourceCallbacks( ClientDatabase& clientDatabase );
// 	};
// }
