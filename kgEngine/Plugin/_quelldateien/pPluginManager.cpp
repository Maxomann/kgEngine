#include "../pPluginManager.h"

PLUGIN_API void kg::pPluginManager::loadPluginsFromFile( const std::string& path )
{
#ifdef _WIN32

	HMODULE dllHandle = LoadLibrary( path.c_str() );
	CONNECT connectFunction = ( CONNECT )GetProcAddress( dllHandle, "connect" );

	if( connectFunction != NULL )
	{
		CONNECT( this );
	}
	else
	{
		REPORT_ERROR_PLUGIN( "connect function on file " + path + " failed!" );
	}

#endif // _WIN32
}