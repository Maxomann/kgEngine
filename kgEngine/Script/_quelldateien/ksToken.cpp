#include "../ksToken.h"

kg::ksToken::ksToken( int firstLineOfToken, int lastLineOfToken )
:m_lastLineOfToken( lastLineOfToken ),
m_firstLineOfToken(firstLineOfToken)
{ }

int kg::ksToken::getLastLine() const
{
	return m_lastLineOfToken;
}

int kg::ksToken::getFirstLine() const
{
	return m_firstLineOfToken;
}