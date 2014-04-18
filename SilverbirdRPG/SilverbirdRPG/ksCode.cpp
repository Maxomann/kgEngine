#include "ksCode.h"

namespace kg
{
	namespace key
	{
		static enum
		{
			alphabetic,//abc...
			digit,//123...
			mathLogic,//+ - * / < > ! = :
			space,
			other
		};
	}
	namespace status
	{
		static enum
		{
			inString,
			other
		};
	}

	static void pushTokenWithId( ksSplitCodeVector& splitCode,
								 const std::string& temp,
								 const ksRawTokenMap& rawTokens )
	{
		if( temp == "" )
			return;

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

	static void setLastKey( const char ch, int& k )
	{
		if( std::isalpha( ch ) )
			k = key::alphabetic;
		else if( isdigit( ch ) )
			k = key::digit;
		else if( ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '<' || ch == '>' || ch == '!' || ch == '=' || ch == ':' )
			k = key::mathLogic;
		else if( std::isspace( ch ) )
			k = key::space;
		else
			k = key::other;
	}

	kg::ksSplitCodeVector ksCode::generateSplitCode( const ksRawTokenMap& rawTokens, const std::string& code )
	{

		ksSplitCodeVector splitCode;
		int lastKey = key::other;
		int stat=status::other;

		std::string temp;

		for( const char& el : code )
		{
			if( stat == status::inString )
			{
				//endString
				if( el == '\"' )
				{
					splitCode.push_back( std::make_pair( temp, ksRAW_TOKEN_ID::_IDENTIFIER ) );
					temp.clear();
					stat = status::other;
					lastKey = key::other;
					temp.push_back( el );
				}
				else
				{
					temp.push_back( el );
				}
			}
			else//status==other
			{
				//beginString
				if( el == '\"' )
				{
					pushTokenWithId( splitCode, temp, rawTokens );
					temp.clear();
					splitCode.push_back( std::make_pair( "\"", ksRAW_TOKEN_ID::_STRING ) );
					stat = status::inString;
				}
				else
				{
					//not inString and not beginString
					switch( lastKey )
					{
					case key::alphabetic:
						setLastKey( el, lastKey );
						if( lastKey == key::alphabetic || lastKey == key::digit )
							//stays alphabetic even if it is a number
							temp.push_back( el );
						else
						{
							pushTokenWithId( splitCode, temp, rawTokens );
							temp.clear();
							//el cannot be alphabetic or digit here
							if( lastKey != key::space )
								temp.push_back( el );
						}
						break;
					case key::digit:
						setLastKey( el, lastKey );
						if( lastKey == key::digit )
							temp.push_back( el );
						else
						{
							pushTokenWithId( splitCode, temp, rawTokens );
							temp.clear();
							if( lastKey != key::space )
								temp.push_back( el );
						}
						break;
					case key::mathLogic:
						setLastKey( el, lastKey );
						if( lastKey == key::mathLogic )
							temp.push_back( el );
						else
						{
							pushTokenWithId( splitCode, temp, rawTokens );
							temp.clear();
							if( lastKey != key::space )
								temp.push_back( el );
						}
						break;
					case key::space:
						setLastKey( el, lastKey );
						if( lastKey != key::space )
							temp.push_back( el );
						break;
					case key::other:
						setLastKey( el, lastKey );
						pushTokenWithId( splitCode, temp, rawTokens );
						temp.clear();
						if( lastKey != key::space )
							temp.push_back( el );
						break;
					}
				}
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
		m_constructTokens( tokenConstructors, generateSplitCode( rawTokens, code ) );
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