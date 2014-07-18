// #include "../ClientDatabaseResourceUser.h"
// 
// namespace kg
// {
// 
// 
// 	TileResourceUser::TileResourceUser( ClientDatabase& clientDatabase )
// 	{
// 		onRegisterResourceCallbacks( clientDatabase );
// 	}
// 
// 	void TileResourceUser::onRegisterResourceCallbacks( ClientDatabase& clientDatabase )
// 	{
// 		clientDatabase.registerCallback( this,
// 										 std::bind(
// 										 &TileResourceUser::onTilesModiefied,
// 										 this,
// 										 std::placeholders::_1,
// 										 std::placeholders::_2),
// 										 CALLBACK_ID::CLIENT_DATABASE::TILE_MODIFIED );
// 	}
// 
// 
// 	ConfigFileUser::ConfigFileUser( ClientDatabase& clientDatabase )
// 	{
// 		onRegisterResourceCallbacks( clientDatabase );
// 	}
// 
// 	void ConfigFileUser::onRegisterResourceCallbacks( ClientDatabase& clientDatabase )
// 	{
// 		clientDatabase.registerCallback( this,
// 										 std::bind(
// 										 &ConfigFileUser::onResourceFileModified,
// 										 this,
// 										 std::placeholders::_1,
// 										 std::placeholders::_2 ),
// 										 CALLBACK_ID::CLIENT_DATABASE::TILE_MODIFIED );
// 	}
// 
// }
