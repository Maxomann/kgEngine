//_______LIBRARY_______//

#pragma once
#include "../stdafx.h"
#include "ksClass.h"
#include "ksFunction.h"
#include "ksFunctionWrapper.h"
#include <Algorithm/aException.h>

namespace kg
{
	class ksLibrary
	{
		std::map<std::string, std::shared_ptr<ksClassMasterInterface>> m_availableTypesByName;
		std::map<size_t, std::shared_ptr<ksClassMasterInterface>> m_availableTypesByHash;

		std::map<std::string, std::shared_ptr<ksFunctionMaster>> m_availableFunctions;

//		ksCodeVector m_subCode;

	public:
		void registerType( const std::shared_ptr<ksClassMasterInterface>& type );

		template<class T>
		const std::shared_ptr<ksClassMasterInterface>& getType()const;

		const std::shared_ptr<ksClassMasterInterface>& getType( const std::string& name )const;
		const std::shared_ptr<ksClassMasterInterface>& getType( size_t hash )const;

		void registerFunction( const std::shared_ptr<ksFunctionMaster>& funcMaster );
		const std::shared_ptr<ksFunctionMaster>& getFunction( const std::string& name );

// 		int registerSubCode( const std::shared_ptr<ksCode>& subCode );
// 		std::shared_ptr<ksCode>& getSubCode( int position );

		ksTokenConstructorPriorityMap tokenConstructors;
		ksRawTokenMap rawTokens;
	};

	template<class T>
	const std::shared_ptr<ksClassMasterInterface>
		& kg::ksLibrary::getType() const
	{
			return m_availableTypesByHash.at( typeid(T).hash_code() );
	}

}