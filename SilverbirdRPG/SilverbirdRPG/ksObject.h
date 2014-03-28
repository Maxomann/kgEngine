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
									 ksMemberFunction& function );

		const std::string& getType()const;
	};

	class ksObject
	{
		const ksParent& r_parent;

		std::shared_ptr<void> m_cppObject;

	public:
		ksObject( const ksParent& parent );

		//returns nullptr on fail
		std::shared_ptr<ksObject> callMemberFunction( const std::string& name,
													  const ksObjectVector& arguments );

		const std::string& getType()const;
	};
}