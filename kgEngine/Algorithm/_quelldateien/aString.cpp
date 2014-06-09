//_______ALGORITHM_STRING_CPP_______//

#pragma once
#include "../aString.h"

namespace kg
{
	namespace aSplitString
	{
		std::vector< std::string > function( std::string toSplit, std::vector< char > atChars, operation op )
		{
			std::vector< std::string > words;
			words.push_back( std::string() );
			int i = 0;

			for( char ch : toSplit )
			{
				if( std::any_of( atChars.begin(), atChars.end(), kg::aIsEqualTo<char>( ch ) ) )
				{
					switch( op )
					{
					case operation::REMOVE:
						words.push_back( std::string() );
						i++;
						break;
					case operation::ADD_THISWORD:
						words.at( i ) += ch;
						words.push_back( std::string() );
						i++;
						break;
					case operation::ADD_NEXTWORD:
						words.push_back( std::string() );
						i++;
						words.at( i ) += ch;
						break;
					default:
						words.push_back( std::string() );
						i++;
						break;
					}
				}
				else
				{
					words.at( i ) += ch;
				}
			}

			//Leere wörter entfernen
			words.erase( std::remove( words.begin(), words.end(), "" ), words.end() );

			return words;
		};
		std::vector< std::string > function( std::string toSplit, char atChar_a, aSplitString::operation op )
		{
			std::vector< char > atChars;
			atChars.push_back( atChar_a );

			return function( toSplit, atChars, op );
		};
		std::vector< std::string > function( std::string toSplit, char atChar_a, char atChar_b, aSplitString::operation op )
		{
			std::vector< char > atChars;
			atChars.push_back( atChar_a );
			atChars.push_back( atChar_b );

			return function( toSplit, atChars, op );
		};
		std::vector< std::string > function( std::string toSplit, char atChar_a, char atChar_b, char atChar_c, aSplitString::operation op )
		{
			std::vector< char > atChars;
			atChars.push_back( atChar_a );
			atChars.push_back( atChar_b );
			atChars.push_back( atChar_c );

			return function( toSplit, atChars, op );
		};
		std::vector< std::string > function( std::string toSplit, char atChar_a, char atChar_b, char atChar_c, char atChar_d, aSplitString::operation op )
		{
			std::vector< char > atChars;
			atChars.push_back( atChar_a );
			atChars.push_back( atChar_b );
			atChars.push_back( atChar_c );
			atChars.push_back( atChar_d );

			return function( toSplit, atChars, op );
		};
		std::vector< std::string > function( std::string toSplit, char atChar_a, char atChar_b, char atChar_c, char atChar_d, char atChar_e, aSplitString::operation op )
		{
			std::vector< char > atChars;
			atChars.push_back( atChar_a );
			atChars.push_back( atChar_b );
			atChars.push_back( atChar_c );
			atChars.push_back( atChar_d );
			atChars.push_back( atChar_e );

			return function( toSplit, atChars, op );
		};
	};//aSplitString
};//kg