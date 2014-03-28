#include "ksObject.h"

kg::ksParent::ksParent( const std::string& type )
:m_type( type )
{ }

std::shared_ptr<kg::ksObject> kg::ksParent::callMemberFunction( const std::shared_ptr<void>& cppObject,
																const std::string& name,
																const ksObjectVector& arguments )const
{
	for( const ksMemberFunction& el : m_memberFunctions.at( name ) )
	{
		auto retVal = el( cppObject, arguments );
		if( retVal != nullptr )
			return retVal;
	}
	return std::shared_ptr<kg::ksObject>();
}

const std::string& kg::ksParent::getType() const
{
	return m_type;
}

void kg::ksParent::registerMemberFunction( const std::string& name,
										   ksMemberFunction& function )
{
	m_memberFunctions[name].push_back( function );
}

kg::ksObject::ksObject( const ksParent& parent )
:r_parent( parent )
{ }

std::shared_ptr<kg::ksObject> kg::ksObject::callMemberFunction( const std::string& name,
																const ksObjectVector& arguments )
{
	return r_parent.callMemberFunction( m_cppObject, name, arguments );
}

const std::string& kg::ksObject::getType() const
{
	return r_parent.getType();
}