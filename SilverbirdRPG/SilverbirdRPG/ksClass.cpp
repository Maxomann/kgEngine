#include "ksClass.h"




kg::ksClassMasterInterface::ksClassMasterInterface( const std::string& name, const size_t& typeHash )
:m_typeHash( typeHash ),
m_name( name )
{

}

void kg::ksClassMasterInterface::registerMemberFunction( const std::vector<std::string>& parameterTypes,
														 const std::shared_ptr<ksMemberFunctionWrapperInterface>& function )
{
	m_memberFunctions[parameterTypes] = function;
}

void kg::ksClassMasterInterface::callMemberFunction( const std::vector<std::string>& parameterTypes,
																					 const std::shared_ptr<void>& cppObj,
																					 const std::vector<std::shared_ptr<ksClassInstance>>& args ) const
{
	std::vector<std::shared_ptr<void>> argsConverted;
	for( const auto& obj : args )
		argsConverted.push_back( std::shared_ptr<void>( obj->getCppInstance() ) );

	m_memberFunctions.at( parameterTypes )->call( cppObj, argsConverted );
}

const std::string& kg::ksClassMasterInterface::getType() const
{
	return m_name;
}

kg::ksClassInstance::ksClassInstance( ksClassMasterInterface& master,
									  const std::shared_ptr<void>& instance )
									  :m_instance( m_instance ),
									  r_master( master )
{

}

const std::string& kg::ksClassInstance::getType() const
{
	return r_master.getType();
}

void kg::ksClassInstance::callMemberFunction( const std::vector<std::string>& parameterTypes,
																			  const std::vector<std::shared_ptr<ksClassInstance>>& args ) const
{
	r_master.callMemberFunction( parameterTypes, m_instance, args );
}
