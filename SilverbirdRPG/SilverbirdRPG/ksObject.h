//_______CODE_H_______//

#pragma once
#include "stdafx.h"
#include "ksSyntax.h"

namespace kg
{
	class ksParent
	{
		const std::string m_type;

		std::map<std::string, std::vector<ksMemberFunction>> m_memberFunctions;

	public:
		ksParent( const std::string& type );

		//returns nullptr on fail
		std::shared_ptr<ksObject> callMemberFunction( const std::shared_ptr<void>& cppObject,
													  const std::string& name,
													  const ksObjectVector& arguments )const;

		void registerMemberFunction( const std::string& name,
									 const ksMemberFunction& function );

		const std::string& getType()const;
	};

	class ksObject
	{
		const ksParent& r_parent;

		const std::shared_ptr<void> m_cppObject;

		const size_t m_cppTypeHash;

	public:
		ksObject( const std::shared_ptr<void>& cppObject,
				  const size_t& cppObjectTypeHash,
				  const ksParent& parent );

		//returns nullptr on fail
		std::shared_ptr<ksObject> callMemberFunction( const std::string& name,
													  const ksObjectVector& arguments );

		const std::string& getType()const;

		const size_t& getCppTypeHash()const;

		template< class T=void >
		std::shared_ptr<T> toCppObject();
	};

	template< class T >
	std::shared_ptr<T> ksObject::toCppObject()
	{
		return std::static_pointer_cast< T >(m_cppObject);
	}



	namespace ksFunctions
	{
		static const std::string Constructor = "CONSTRUCTOR";
	}
	namespace ksTypes
	{
		static const std::string Bool = "bool";
	}
}