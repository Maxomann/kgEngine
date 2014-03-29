#include "ksToken.h"

kg::ksToken::ksToken( const int endOfToken )
:m_endOfToken( endOfToken )
{ }

unsigned int kg::ksToken::getEndOfToken() const
{
	return m_endOfToken;
}
