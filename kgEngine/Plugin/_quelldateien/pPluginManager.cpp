#include "../pPluginManager.h"

PLUGIN_API void kg::pPluginManager::loadPluginsFromFile( const std::string& path )
{
#ifdef _WIN32

	HMODULE dllHandle = LoadLibrary( path.c_str() );

	if( !dllHandle )
	{
		REPORT_ERROR_PLUGIN( "LoadLibrary() on file " + path + " failed!" );
	}

	CONNECT connectFunction = (CONNECT)GetProcAddress( dllHandle, "kgConnect" );

	if( !connectFunction )
	{
		REPORT_ERROR_PLUGIN( "connect function in file " + path + " could not be loaded!" );
	}
	
	connectFunction( *this );

#elif
#error TARGET_PLATTFORM_NOT_SUPPORTED
#endif // _WIN32
}
