//_______ALGORITHM_STRING_H_______//

#pragma once
#include "aBase.h"
#include "stdafx.h"

namespace kg
{
	namespace aSplitString
	{
		//////////////////////////////////////////////////
		///
		/// \brief enum operation
		/// Define what to do with the chars where the string gets split at
		/// ex.
		///
		/// \code
		/// vector< char > atChars;
		/// atChars.push_back('Z');
		/// string::split::operation op;
		/// auto words = string::split::function( "HelloZdude", atChars, op );
		///
		/// for( auto word : words )
		///	  cout<<word<<endl;
		/// \endcode
		///
		/// output:
		///
		///	 op == REMOVE:
		///		Hello
		///		dude
		///
		///  op == ADD_THISWORD:
		///		HelloZ
		///		dude
		///
		///  op == ADD_NEXTWORD
		///		Hello
		///		Zdude
		///
		///
		//////////////////////////////////////////////////
		enum operation
		{
			REMOVE,
			ADD_THISWORD,
			ADD_NEXTWORD
		};

		//////////////////////////////////////////////////
		///
		/// \brief function
		/// to split a std::string in parts at defined chars.
		/// These chars can wether be given in a vector or up to five chars as arguments.
		///
		/// \see operation
		///
		//////////////////////////////////////////////////
		std::vector< std::string > ALGORITHM_API function( std::string toSplit, std::vector< char > atChars, aSplitString::operation op );
		std::vector< std::string > ALGORITHM_API function( std::string toSplit, char atChar_a, aSplitString::operation op );
		std::vector< std::string > ALGORITHM_API function( std::string toSplit, char atChar_a, char atChar_b, aSplitString::operation op );
		std::vector< std::string > ALGORITHM_API function( std::string toSplit, char atChar_a, char atChar_b, char atChar_c, aSplitString::operation op );
		std::vector< std::string > ALGORITHM_API function( std::string toSplit, char atChar_a, char atChar_b, char atChar_c, char atChar_d, aSplitString::operation op );
		std::vector< std::string > ALGORITHM_API function( std::string toSplit, char atChar_a, char atChar_b, char atChar_c, char atChar_d, char atChar_e, aSplitString::operation op );
	};
};//kg