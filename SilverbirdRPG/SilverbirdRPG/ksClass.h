//_______CODE_H_______//

#pragma once
#include "stdafx.h"
#include "ksSyntax.h"
#include "ksFunctionWrapper.h"
#include "aException.h"

namespace kg
{

	class ksClassInstance;

	class ksClassMasterInterface
	{
		const std::string m_name;
		const size_t m_typeHash;

		std::map<std::string, std::map < std::vector<std::string>, std::shared_ptr<ksMemberFunctionWrapperInterface>>> m_memberFunctions;

	public:
		ksClassMasterInterface( const std::string& name, const size_t& typeHash );

		void registerMemberFunction( const std::string& name, const std::vector<std::string>& parameterTypes,
									 const std::shared_ptr<ksMemberFunctionWrapperInterface>& function );

		//args have to be IN ORDER of signature you want to call
		// RETURN_VALUE:
		// if pair.first==NULL:
		//		pair.second = std::shared_ptr<ksClassInstance>
		// if pair.first!=NULL:
		//		pair.first=hash
		//		pair.second = std::shared_ptr<void>
		//		TODO: lib.getType( retVal.first )->createInstance( retVal.second );
		//	
		std::pair<size_t, std::shared_ptr<void>> callMemberFunction( const std::string& name, const std::vector<std::string>& parameterTypes, const std::shared_ptr<void>& cppObj, const std::vector<std::shared_ptr<ksClassInstance>>& args )const;

		const std::string& getType()const;

		//check with m_typeHash
		template<class T>
		std::shared_ptr<ksClassInstance> createInstance( T* instance )const;

		std::shared_ptr<ksClassInstance> createInstance( const std::shared_ptr<void>& instance )const;

		//creates new Instance
		virtual std::shared_ptr<ksClassInstance> createNewInstance()const = 0;
	};

	template<class T>
	class ksClassMaster : public ksClassMasterInterface
	{
	public:
		ksClassMaster( const std::string& name, const size_t& typeHash )
			:ksClassMasterInterface( name, typeHash )
		{ }

		std::shared_ptr<ksClassInstance> createNewInstance()const
		{
			return std::make_shared<ksClassInstance>( *this, std::static_pointer_cast< void >(std::make_shared<T>()) );
		};
	};

	class ksClassInstance
	{
		const ksClassMasterInterface& r_master;

		std::shared_ptr<void> m_instance;

	public:
		ksClassInstance( const ksClassMasterInterface& master, const std::shared_ptr<void>& instance );

		const std::string& getType()const;

		template<class T = void>
		const std::shared_ptr<void>& getCppInstance()const;

		//args have to be IN ORDER of signature you want to call
		// RETURN_VALUE:
		// if pair.first==NULL:
		//		pair.second = std::shared_ptr<ksClassInstance>
		// if pair.first!=NULL:
		//		pair.first=hash
		//		pair.second = std::shared_ptr<void>
		//		TODO: lib.getType( retVal.first )->createInstance( retVal.second );
		//	
		std::pair<size_t, std::shared_ptr<void>> callMemberFunction( const std::string& name, const std::vector<std::string>& parameterTypes, const std::vector<std::shared_ptr<ksClassInstance>>& args )const;
	};

	template<class T>
	std::shared_ptr<ksClassInstance>
		ksClassMasterInterface::createInstance( T* instance ) const
	{
			return new ksClassInstance( *this, std::static_pointer_cast< void >(std::shared_ptr<T>( instance )) );
	}

	template<class T/*=void*/>
	const std::shared_ptr<void>& kg::ksClassInstance::getCppInstance() const
	{
		return m_instance;
	}

}