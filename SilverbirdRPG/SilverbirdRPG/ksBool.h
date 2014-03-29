//_______BOOL_______//

#include "stdafx.h"
#include "ksObject.h"

namespace kg
{
	std::shared_ptr<ksParent> ksCreateParentBool()
	{
		auto ptr = std::make_shared<ksParent>( ksTypes::Bool );

		//CONSTRUCTOR
		ptr->registerMemberFunction( ksFunctions::Constructor,
									 []( const std::shared_ptr<void>& cppObject,
									 const ksObjectVector& arguments )->std::shared_ptr<ksParent>
		{
			auto object = std::static_pointer_cast< bool >(cppObject);

			if( arguments.size() != 1 )
			{
				return nullptr;
			}
			else if( arguments.at( 0 )->getType() != ksTypes::Bool )
			{
				return nullptr;
			}
			else
			{
				*object = *arguments.at( NULL )->toCppObject<bool>();
			}
		} );
	}
}