//_______FUNCTION_______//

#include "stdafx.h"
#include "ksFunctionWrapper.h"
#include "ksClass.h"
#include "aException.h"
#include "ksCode.h"


namespace kg
{
	class ksLibrary;

	class ksScriptFunctionOverload
	{
		const std::shared_ptr<ksCode> m_code;
		const std::vector<std::string> m_parameterNamesLeftToRight;
	public:
		ksScriptFunctionOverload( const std::vector<std::string>& parameterNamesLeftToRight,
								  const std::shared_ptr<ksCode>& code );

		//TODO
		std::shared_ptr<ksClassInstance> call( ksLibrary& library,
											   const std::vector<std::shared_ptr<ksClassInstance>>& parameters )const;
	};

	class ksFunctionMaster
	{
		const std::string m_name;

		std::map<std::vector<std::string>, std::shared_ptr<ksFunctionWrapperInterface>> m_boundOverloads;
		std::map<std::vector<std::string>, std::shared_ptr<ksScriptFunctionOverload>> m_scriptOverloads;

	public:
		ksFunctionMaster( const std::string& name );

		const std::string& getName()const;

		//parameterTypes witout qualifiers!
		void registerOverload( const std::vector<std::string>& parameterTypes,
							   const std::shared_ptr<ksFunctionWrapperInterface>& function );
		//parameterTypes witout qualifiers!
		void registerOverload( const std::vector<std::string>& parameterTypes,
							   const std::shared_ptr<ksScriptFunctionOverload>& function );

		//args have to be IN ORDER of signature you want to call
		// RETURN_VALUE:
		// if pair.first==NULL:
		//		pair.second = std::shared_ptr<ksClassInstance>
		// if pair.first!=NULL:
		//		pair.first=hash
		//		pair.second = std::shared_ptr<void>
		//		TODO: lib.getType( retVal.first )->createInstance( retVal.second );
		//		EXCEPTION:
		//			if pair.second==nullptr: return type is void
		//		
		std::pair<size_t, std::shared_ptr<void>> call( ksLibrary& library,
													   const std::vector<std::shared_ptr<ksClassInstance>>& parameters )const;
		//TODO
	};

	template< class Ret, typename...Args >
	void ksRegisterFunction( ksFunctionMaster& functionMaster,
							 const std::vector<std::string>& parameterTypes,
							 Ret( *function )(Args...) )
	{
		functionMaster.registerOverload( parameterTypes,
										 std::make_shared<ksFunctionWrapper<Ret( Args... )>>( function ) );
	}

}