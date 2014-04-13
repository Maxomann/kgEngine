#include "ksClass.h"




kg::ksClassMasterInterface::ksClassMasterInterface( const std::string& name,
													const size_t& typeHash )
													:m_typeHash( typeHash ),
													m_name( name )
{

}

void kg::ksClassMasterInterface::registerMemberFunction( const std::string& name,
														 const std::vector<std::string>& parameterTypes,
														 const std::shared_ptr<ksMemberFunctionWrapperInterface>& function )
{
	m_memberFunctions[name][parameterTypes] = function;
}

std::pair<size_t, std::shared_ptr<void>> kg::ksClassMasterInterface::callMemberFunction( const std::string& name,
																						 const std::vector<std::string>& parameterTypes,
																						 const std::shared_ptr<void>& cppObj,
																						 const std::vector<std::shared_ptr<ksClassInstance>>& args ) const
{
	try
	{
		std::vector<std::shared_ptr<void>> argsConverted;
		for( const auto& obj : args )
			argsConverted.push_back( std::shared_ptr<void>( obj->getCppInstance() ) );

		return m_memberFunctions.at( name ).at( parameterTypes )->call( cppObj, argsConverted );
	}
	catch( std::exception& e )
	{
		std::string parameters;
		for( const auto& el : parameterTypes )
			parameters+=( el+"," );

		REPORT_ERROR_SCRIPT( "callMemberFunction() wrong function call\n#name: "+name+"\n#parameterTypes: "+parameters );
	}
}

const std::string& kg::ksClassMasterInterface::getType() const
{
	return m_name;
}

std::shared_ptr<kg::ksClassInstance> kg::ksClassMasterInterface::createInstance( const std::shared_ptr<void>& instance ) const
{
	return std::make_shared<ksClassInstance>( *this, instance );
}

kg::ksClassInstance::ksClassInstance( const ksClassMasterInterface& master,
									  const std::shared_ptr<void>& instance )
									  :m_instance( instance ),
									  r_master( master )
{

}

const std::string& kg::ksClassInstance::getType() const
{
	return r_master.getType();
}

std::pair<size_t, std::shared_ptr<void>> kg::ksClassInstance::callMemberFunction( const std::string& name, const std::vector<std::string>& parameterTypes, const std::vector<std::shared_ptr<ksClassInstance>>& args ) const
{
	return r_master.callMemberFunction( name, parameterTypes, m_instance, args );
}
