#include "ksCode.h"

namespace kg
{
	static void pushTokenWithId( ksSplitCodeVector& splitCode,
								 const std::string& temp,
								 const ksRawTokenMap& rawTokens )
	{
		for( const auto& el : rawTokens )
		{
			if( el.first == temp )
			{
				splitCode.push_back( std::make_pair( temp, el.second ) );
				return;
			}
		}
		splitCode.push_back( std::make_pair( temp, ksRAW_TOKEN_ID::_IDENTIFIER ) );
	}

	kg::ksSplitCodeVector ksCode::m_generateSplitCode( const ksRawTokenMap& rawTokens, const std::string& code ) const
	{
		ksSplitCodeVector splitCode;

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
					splitCode.push_back( std::make_pair( temp, ksRAW_TOKEN_ID::_VALUE_STRING ) );
					temp.clear();
					pushTokenWithId( splitCode, "\"", rawTokens );
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
					pushTokenWithId( splitCode, temp, rawTokens );
				temp.clear();
				pushTokenWithId( splitCode, "\"", rawTokens );
			}
			else if( std::isalpha( el ) || el == '_' )
			{
				if( !lastWasAlpha )
				{
					if( temp.size() > 0 )
					{
						pushTokenWithId( splitCode, temp, rawTokens );
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
					pushTokenWithId( splitCode, temp, rawTokens );
					temp.clear();
				}
			}
			else
			{
				if( temp.size() > 0 )
				{
					pushTokenWithId( splitCode, temp, rawTokens );
					temp.clear();
				}
				std::string str;
				str.push_back( el );
				pushTokenWithId( splitCode, str, rawTokens );
				lastWasAlpha = false;
			}
		}

		if( splitCode.size() == NULL )
			REPORT_ERROR_SCRIPT( "splitCode.size() == 0" );
		return splitCode;
	}

	ksCode::ksCode( const ksTokenConstructorPriorityMap& tokenConstructors,
					const ksRawTokenMap& rawTokens,
					const std::string& code )
	{
		m_constructTokens( tokenConstructors, m_generateSplitCode( rawTokens, code ) );
	}

	ksCode::ksCode( const ksTokenConstructorPriorityMap& tokenConstructors,
					const ksSplitCodeVector& splitCode )
	{
		m_constructTokens( tokenConstructors, splitCode );
	}

	void ksCode::m_constructTokens( const ksTokenConstructorPriorityMap& tokenConstructors,
									const ksSplitCodeVector& splitCode )
	{
		for( const std::pair<int, std::vector<std::shared_ptr<ksTokenConstructor>>>& priority : tokenConstructors )
		{
			for( unsigned int currentLine = 0; currentLine < splitCode.size(); )
			{
				if( m_constructedTokens[currentLine] == nullptr )
				{
					for( const std::shared_ptr<ksTokenConstructor>& constructor : priority.second )
					{
						if( constructor->construct( splitCode, m_constructedTokens, currentLine ) )
						{
							currentLine = m_constructedTokens[currentLine]->getLastLine() + 1;
							break;//
						}
					}
					//break here
				}
				else
				{
					currentLine = m_constructedTokens[currentLine]->getLastLine() + 1;
				}
			}
		}
	}

	std::shared_ptr<kg::ksClassInstance> ksCode::execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack )const
	{
		if( m_constructedTokens.size() == NULL )
			REPORT_ERROR_SCRIPT( "m_constructedTokens.size()==0" );

		std::shared_ptr<ksClassInstance> returnValue = nullptr;

		for( int currentLine = 0; currentLine <= m_constructedTokens.rbegin()->first; )
		{
			auto& token = m_constructedTokens.at( currentLine );

			//not expected to return anything
			token->execute( library,
							stack,
							returnValue );

			currentLine = token->getLastLine() + 1;
		}

		return returnValue;
	}
}