//_______SYNTAX_H_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class ksToken;
	class ksClassInstance;
	class ksTokenConstructor;
	class ksCode;
	class ksClassWrapper;
	class ksClassMasterInterface;

	typedef std::vector<std::shared_ptr<ksClassInstance>> ksObjectVector;
	typedef std::vector<ksCode> ksCodeOperationVector;
	typedef std::map<int, std::shared_ptr<ksToken>> ksTokenMap;
	typedef std::map<int, std::vector<std::shared_ptr<ksTokenConstructor>>> ksTokenConstructorMap;
	typedef std::map<std::string, std::shared_ptr<ksClassInstance>> ksObjectMap;
	typedef std::map<std::string, std::shared_ptr<ksClassWrapper>> ksParentMap;

	struct ksReferenceContainer
	{
		ksParentMap& availableCppObjectTypes;
		ksObjectMap& stack;

	public:
		ksReferenceContainer( ksParentMap& availableCppObjectTypes,
							  ksObjectMap& stack )
							  :availableCppObjectTypes( availableCppObjectTypes ),
							  stack( stack )
		{ };
	};
}