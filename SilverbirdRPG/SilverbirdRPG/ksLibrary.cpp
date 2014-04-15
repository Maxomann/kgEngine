#include "ksLibrary.h"

namespace kg
{
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

	int kg::ksLibrary::registerSubCode( const std::shared_ptr<ksCode>& subCode )
	{
		m_subCode.push_back( subCode );
		return m_subCode.size() - 1;
	}

	std::shared_ptr<ksCode>& kg::ksLibrary::getSubCode( int position )
	{
		return m_subCode.at( position );
	}
}