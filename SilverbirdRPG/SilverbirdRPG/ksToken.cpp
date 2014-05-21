#include "ksToken.h"

kg::ksToken::ksToken( int firstLineOfToken, int lastLineOfToken, int lastLineWhileConstruction )
:m_lastLineOfToken( lastLineOfToken ),
m_firstLineOfToken(firstLineOfToken),
m_lastLineWhileConstruction(lastLineWhileConstruction)
{ }

int kg::ksToken::getLastLine() const
{
	return m_lastLineOfToken;
}

int kg::ksToken::getFirstLine() const
{
	return m_firstLineOfToken;
}

int kg::ksToken::getlastLineWhileConstruction() const
{
	return m_lastLineWhileConstruction;
}
