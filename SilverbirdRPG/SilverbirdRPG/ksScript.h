//_______SCRIPT_______//

#pragma once
#include "stdafx.h"
#include "ksCode.h"
#include "aException.h"
#include "ksLibrary.h"

namespace kg
{
	class ksScript
	{
		ksLibrary& r_library;

		bool m_isInterpreted = false;

		std::string m_code;

		std::map<std::string, std::shared_ptr<ksClassInstance>> m_stack;

	public:
		ksScript( ksLibrary& library );

		bool loadFromFile( const std::string& path );
		bool loadFromString( const std::string& code );

		std::shared_ptr<ksClassInstance> interpret();

		bool isInterpreted()const;

		bool isLoaded()const;
	};


	///////////KS_SCRIPT HELPER_FUNCTIONS:

	void ksRegisterStandartTypes( ksLibrary& library );
	std::shared_ptr<ksClassInstance> ksRunScript( ksLibrary& library, const std::string& path );

	template<class T>
	std::shared_ptr<ksClassMasterInterface> ksCreateClassMaster( const std::string& name )
	{
		return std::make_shared<ksClassMaster<T>>( name, typeid(T).hash_code() );
	}

	std::shared_ptr<ksFunctionMaster> ksCreateFunctionMaster( const std::string& name );

	//Non const member function
	template<class Obj, class Ret, typename ... Args>
	void ksRegisterMemberFunction( std::shared_ptr<ksClassMasterInterface>& classMaster,
								   const std::string& name,
								   const std::vector<std::string>& parameterTypes,
								   Ret( Obj::*function )(Args...) )
	{
		classMaster->registerMemberFunction( name,
											 parameterTypes,
											 std::make_shared<ksFunctionWrapper<decltype(function)>>( function ) );
	}

	//Const member function
	template<class Obj, class Ret, typename ... Args>
	void ksRegisterMemberFunction( std::shared_ptr<ksClassMasterInterface>& classMaster,
								   const std::string& name,
								   const std::vector<std::string>& parameterTypes,
								   Ret( Obj::*function )(Args...)const )
	{
		classMaster->registerMemberFunction( name,
											 parameterTypes,
											 std::make_shared<ksFunctionWrapper<decltype(function)>>( function ) );
	}

	template< class Ret, typename...Args >
	void ksRegisterOverload( const std::shared_ptr<ksFunctionMaster>& functionMaster,
							 const std::vector<std::string>& parameterTypes,
							 Ret( *function )(Args...) )
	{
		functionMaster->registerOverload( parameterTypes,
										  std::make_shared<ksFunctionWrapper<Ret( Args... )>>( function ) );
	}

}