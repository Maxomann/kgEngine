//_______FUNCTION_______//

#include "stdafx.h"
#include "ksFunctionWrapper.h"
#include "ksClass.h"
#include "aException.h"


namespace kg
{

	class ksScriptFunctionOverload
	{
		//TODO
	public:

		std::shared_ptr<ksClassInstance> call(const std::vector<std::shared_ptr<ksClassInstance>>& parameters)const;
	};

	class ksFunctionMaster
	{
		const std::string m_name;

		std::map<std::vector<std::string>, std::shared_ptr<ksFunctionWrapperInterface>> m_boundOverloads;
		std::map<std::vector<std::string>, std::shared_ptr<ksScriptFunctionOverload>> m_scriptOverloads;

	public:
		ksFunctionMaster(const std::string& name);

		const std::string& getName()const;

		//parameterTypes witout qualifiers!
		void registerOverload( const std::vector<std::string>& parameterTypes,
							   const std::shared_ptr<ksFunctionWrapperInterface>& function );
		//parameterTypes witout qualifiers!
		void registerOverload( const std::vector<std::string>& parameterTypes,
							   const std::shared_ptr<ksScriptFunctionOverload>& function );

		//args have to be IN ORDER of signature you want to call
		void call( const std::vector<std::shared_ptr<ksClassInstance>>& args )const;
	};

}