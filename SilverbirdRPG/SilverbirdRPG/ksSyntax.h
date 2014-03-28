//_______SYNTAX_H_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class ksToken;
	class ksObject;
	class ksTokenConstructor;
	class ksCode;
	class ksParent;

	typedef std::vector<std::shared_ptr<ksObject>> ksObjectVector;
	typedef std::vector<ksCode> ksCodeOperationVector;
	typedef std::map<int, std::shared_ptr<ksToken>> ksTokenMap;
	typedef std::map<int, std::vector<std::shared_ptr<ksTokenConstructor>>> ksTokenConstructorMap;
	typedef std::map<std::string, std::shared_ptr<ksObject>> ksObjectMap;
	typedef std::map<std::string, std::shared_ptr<ksParent>> ksParentMap;

	//ksMemberFunction
	typedef std::function< std::shared_ptr<ksObject>( const std::shared_ptr<void>& cppObject,
													  const ksObjectVector& arguments )> ksMemberFunction;
	//ksFunction
	typedef std::function< std::shared_ptr<ksObject>( const ksObjectVector& arguments )> ksFunction;

	typedef std::map<std::string, ksFunction> ksFunctionMap;

	struct ksReferenceContainer
	{
		ksFunctionMap& availableFunctions;
		ksParentMap& availableCppObjectTypes;
		ksObjectMap& stack;

	public:
		ksReferenceContainer( ksFunctionMap& availableFunctions,
							  ksParentMap& availableCppObjectTypes,
							  ksObjectMap& stack )
							  :availableCppObjectTypes( availableCppObjectTypes ),
							  stack( stack ),
							  availableFunctions( availableFunctions )
		{ };
	};
}