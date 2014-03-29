#include "ksCode.h"

kg::ksCode::ksCode( const ksTokenConstructorMap& tokenConstructors,
					std::vector<ksCode>& subCodeContainer,
					const std::string& code )
					: r_subCode( subCodeContainer )
{
	m_generateSplitCode( code );
	m_constructTokens( tokenConstructors );
}

kg::ksCode::ksCode( const ksTokenConstructorMap& tokenConstructors,
					std::vector<ksCode>& subCodeContainer,
					const std::vector<std::string> splitCode )
					:r_subCode(subCodeContainer),
					m_splitCode(splitCode)
{
	m_constructTokens( tokenConstructors );
}

void kg::ksCode::m_constructTokens( const ksTokenConstructorMap& tokenConstructors )
{
	for( const std::pair<int, std::vector<std::shared_ptr<ksTokenConstructor>>>& priority : tokenConstructors )
	{
		for( int currentLine = 0; currentLine < m_splitCode.size(); currentLine++ )
		{
			if( m_tokens[currentLine] == nullptr )
			{
				for( const std::shared_ptr<ksTokenConstructor>& constructor : priority.second )
				{
					if( constructor->construct(
						tokenConstructors,
						m_splitCode[currentLine],
						m_tokens,
						m_splitCode,
						currentLine ) )
					{
						currentLine = m_tokens[currentLine]->getEndOfToken();
						break;//
					}
				}
				//break here
			}
			else
			{
				currentLine = m_tokens[currentLine]->getEndOfToken();
			}
		}
	}
}

//void kg::ksCode::m_genereateSubCode( const ksTokenConstructorMap& tokenConstructors,
//									 std::string& code )
//{
//	std::string newSubcode;
//	std::string mainCode;
//
//	int codeCount = 0;
//	int eckigeKlammerCount = 0;
//
//	for( const auto&el : code )
//	{
//		if( el == '{' )
//		{
//			eckigeKlammerCount++;
//		}
//		else if( el == '}' )
//		{
//			eckigeKlammerCount--;
//
//			if( eckigeKlammerCount == NULL )
//			{
//				r_subCode.emplace_back( tokenConstructors,
//										newSubcode );
//				newSubcode.clear();
//
//				mainCode += "#";
//				mainCode += std::to_string( codeCount );
//				codeCount++;
//			}
//		}
//		else if( eckigeKlammerCount == NULL )
//		{
//			mainCode += el;
//		}
//		else
//		{
//			newSubcode += el;
//		}
//	}
//
//	code = mainCode;
//}

void kg::ksCode::execute( const ksReferenceContainer& refCon )
{
	int position = 0;

	if( m_tokens.size() > NULL )
	{
		while( position < m_tokens.rbegin()->first )
		{
			auto& token = m_tokens.at( position );
			token->execute( refCon );
			position = token->getEndOfToken() + 1;//next step
		}
	}
	else
	{
		std::string code;
		for( const auto& el : m_splitCode )
		{
			code += el;
			code += "\n";
		}
		REPORT_ERROR_SCRIPT( "No token constructed" + "\n#m_splitCode:\n" + code );
	}
}

void kg::ksCode::m_generateSplitCode( const std::string& code )
{
	std::string temp;
	bool isInString = false;
	bool lastWasAlpha = false;
	for( const auto& el : code )
	{
		if( isInString )
		{
			if( el == '"' )
			{
				isInString = false;
				m_splitCode.push_back( temp );
				temp.clear();
				m_splitCode.push_back( "\"" );
			}
			else
			{
				temp.push_back( el );
			}
		}
		else if( el == '"' )
		{
			isInString = true;
			if( temp.size() > 0 )
				m_splitCode.push_back( temp );
			temp.clear();
			m_splitCode.push_back( "\"" );
		}
		else if( std::isalpha( el ) || el == '_' )
		{
			if( !lastWasAlpha )
			{
				if( temp.size() > 0 )
				{
					m_splitCode.push_back( temp );
					temp.clear();
				}
			}
			temp.push_back( el );
			lastWasAlpha = true;
		}
		else if( std::isspace( el ) )
		{
			if( temp.size() > 0 )
			{
				m_splitCode.push_back( temp );
				temp.clear();
			}
		}
		else
		{
			if( temp.size() > 0 )
			{
				m_splitCode.push_back( temp );
				temp.clear();
			}
			std::string str;
			str.push_back( el );
			m_splitCode.push_back( str );
			lastWasAlpha = false;
		}
	}
}
