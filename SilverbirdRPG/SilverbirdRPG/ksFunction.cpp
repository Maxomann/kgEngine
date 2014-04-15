#include "ksFunction.h"


kg::ksFunctionMaster::ksFunctionMaster( const std::string& name )
: m_name( name )
{ }

const std::string& kg::ksFunctionMaster::getName() const
{
	return m_name;
}

void kg::ksFunctionMaster::registerOverload( const std::vector<std::string>& parameterTypes,
											 const std::shared_ptr<ksFunctionWrapperInterface>& function )
{
	//possible overloads with same signature will be overwritten
	m_boundOverloads[parameterTypes] = function;
}

void kg::ksFunctionMaster::registerOverload( const std::vector<std::string>& parameterTypes,
											 const std::shared_ptr<ksScriptFunctionOverload>& function )
{
	//possible overloads with same signature will be overwritten
	m_scriptOverloads[parameterTypes] = function;
}

std::pair<size_t, std::shared_ptr<void>> kg::ksFunctionMaster::call( ksLibrary& library,
																	 const std::map<std::string, ksFunctionMaster>& availableFunctions,
																	 const std::vector<std::shared_ptr<ksClassInstance>>& parameters ) const
{
	//get parameterTypes from args
	std::vector<std::string> parameterTypes;
	for( const auto& el : parameters )
		parameterTypes.push_back( el->getType() );


	//lookup for function

	//look in m_boundOverloads first
	for( const auto& el : m_boundOverloads )
	{
		if( el.first == parameterTypes )
		{
			//execute function
			//registred overloads with same signature will be ignored
			std::vector<std::shared_ptr<void>> argsConverted;
			for( const auto& obj : parameters )
				argsConverted.push_back( std::shared_ptr<void>( obj->getCppInstance() ) );

			return el.second->call( argsConverted );
		}
	}

	//look in m_scriptOverloads
	for( const auto& el : m_scriptOverloads )
	{
		if( el.first == parameterTypes )
		{
			return std::make_pair( NULL, std::static_pointer_cast< void >(el.second->call( library,
				availableFunctions,
				parameters )) );
		}
	}

	//create error message
	std::string argumentSignature;
	for( const auto& el : parameters )
	{
		argumentSignature += el->getType();
		argumentSignature += ",";
	}
	REPORT_ERROR_SCRIPT( "could not find overload with argumentSignature: " + argumentSignature + "in function" + m_name );

}

std::shared_ptr<kg::ksClassInstance> kg::ksScriptFunctionOverload::call( ksLibrary& library,
																		 const std::map<std::string, ksFunctionMaster>& availableFunctions,
																		 const std::vector<std::shared_ptr<ksClassInstance>>& parameters ) const
{
	std::map<std::string, std::shared_ptr<ksClassInstance>> parameterStack;

	//put argumets on stack
	auto myIt = m_parameterNamesLeftToRight.begin();
	for( auto parIt = parameters.begin(); parIt != parameters.end(); ++parIt )
	{
		parameterStack[*myIt] = *parIt;
		++myIt;
	}

	return m_code.execute( library,
						   availableFunctions,
						   parameterStack );
}

kg::ksScriptFunctionOverload::ksScriptFunctionOverload( const std::vector<std::string>& parameterNamesLeftToRight,
														const ksCode& code )
														:m_code( code ),
														m_parameterNamesLeftToRight( parameterNamesLeftToRight )
{ }
