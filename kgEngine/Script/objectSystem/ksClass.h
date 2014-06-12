//_______CODE_H_______//

#pragma once
#include "../stdafx.h"
#include "ksFunctionWrapper.h"
#include <Algorithm/aException.h>

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
		virtual size_t getHash()const = 0;

		//check with m_typeHash
		//does NOT copy instance!
		template<class T>
		std::shared_ptr<ksClassInstance> createInstance( const std::shared_ptr<T>& instance )const;

		//does NOT copy instance!
		//does NOT check the type of instance!
		std::shared_ptr<ksClassInstance> createInstance( const std::shared_ptr<void>& instance )const;

		//check with m_typeHash
		//copies instance!
		template<class T>
		std::shared_ptr<ksClassInstance> createNewInstance( const T& instance )const;

		//creates new Instance
		//calls default constructor
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

		virtual size_t getHash() const
		{
			return typeid(T).hash_code();
		}
	};

	class ksClassInstance
	{
		const ksClassMasterInterface& r_master;

		std::shared_ptr<void> m_instance;

	public:
		ksClassInstance( const ksClassMasterInterface& master, const std::shared_ptr<void>& instance );

		const std::string& getType()const;

		template<class T = void>
		const std::shared_ptr<T> getCppInstance()const;
		template<>
		const std::shared_ptr<void> getCppInstance()const;

		//args have to be IN ORDER of signature you want to call
		// RETURN_VALUE:
		// if pair.first==NULL:
		//		pair.second = std::shared_ptr<ksClassInstance>
		// if pair.first!=NULL:
		//		pair.first=hash
		//		pair.second = std::shared_ptr<void>
		//		TODO: lib.getType( retVal.first )->createInstance( retVal.second );
		//
		std::pair<size_t, std::shared_ptr<void>> callMemberFunction( const std::string& name, const std::vector<std::shared_ptr<ksClassInstance>>& args )const;
	};

	template<class T>
	std::shared_ptr<ksClassInstance>
		ksClassMasterInterface::createInstance( const std::shared_ptr<T>& instance ) const
	{
		if( typeid(T).hash_code() == m_typeHash )
			return std::make_shared<ksClassInstance>( *this, std::static_pointer_cast< void >(instance) );
		else
		{
			REPORT_ERROR_SCRIPT( "wrong type" );
		}
	}

	template<class T>
	std::shared_ptr<ksClassInstance>
		kg::ksClassMasterInterface::createNewInstance( const T& instance ) const
	{
		if( typeid(T).hash_code() == m_typeHash )
			return std::make_shared<ksClassInstance>( *this, std::make_shared<T>( instance ) );
		else
		{
			REPORT_ERROR_SCRIPT( "wrong type" );
		}
	}

	template<class T/*=void*/>
	const std::shared_ptr<T> kg::ksClassInstance::getCppInstance() const
	{
		if( typeid(T).hash_code() == r_master.getHash() )
			return std::static_pointer_cast< T >(m_instance);
		else
		{
			REPORT_ERROR_SCRIPT( "wrong type" );
		}
	}
	template<>
	const std::shared_ptr<void> kg::ksClassInstance::getCppInstance() const
	{
		return m_instance;
	}
}
