#include "ksLibrary.h"



const std::shared_ptr<kg::ksClassMasterInterface>& kg::ksLibrary::getType( const std::string& name ) const
{
	return m_availableTypesByName.at( name );
}

const std::shared_ptr<kg::ksClassMasterInterface>& kg::ksLibrary::getType( size_t hash ) const
{
	return m_availableTypesByHash.at( hash );
}

void kg::ksLibrary::registerFunction( const std::shared_ptr<ksFunctionMaster>& funcMaster )
{
	m_availableFunctions[funcMaster->getName()] = funcMaster;
}

const std::shared_ptr<kg::ksFunctionMaster>& kg::ksLibrary::getFunction( const std::string& name )
{
	return m_availableFunctions.at( name );
}
