#include "ksToken.h"


kg::ksToken::ksToken( int lastLineOfToken )
:m_lastlineOfToken( lastLineOfToken )
{ }

int kg::ksToken::getLastLine() const
{
	return m_lastlineOfToken;
}
