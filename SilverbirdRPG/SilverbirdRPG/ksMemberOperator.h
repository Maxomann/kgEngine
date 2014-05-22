//_______ksMemberOperator_______//

#pragma once
#include "ksToken.h"
#include "ksLibrary.h"

namespace kg
{
	class ksMemberOperator : public ksToken
	{
	public:
		const std::string m_functionName;
		const std::shared_ptr<ksToken>& m_lhs;
		const std::vector<std::reference_wrapper<std::shared_ptr<ksToken>>> m_args;

	public:
		ksMemberOperator( int firstLineOfToken,
						  int lastLineOfToken,
						  int lastLineWhileConstruction,
						  const std::string& functionName,
						  std::shared_ptr<ksToken>& lhs,
						  const std::vector<std::reference_wrapper<std::shared_ptr<ksToken>>> args )
						  : ksToken( firstLineOfToken, lastLineOfToken, lastLineWhileConstruction ),
						  m_functionName( functionName ),
						  m_args( args ),
						  m_lhs( lhs )
		{ }

		virtual std::shared_ptr<ksClassInstance> execute( ksLibrary& library,
														  std::map<std::string, std::shared_ptr<ksClassInstance>>& stack,
														  std::shared_ptr<ksClassInstance>& functionReturnValue ) const
		{
			std::vector<std::shared_ptr<ksClassInstance>> finalArgs;
			for( auto& el : m_args )
			{
				finalArgs.push_back(
					el.get()->execute( library,
					stack,
					functionReturnValue )
					);
			}

			auto funcRetVal = m_lhs->execute( library, stack, functionReturnValue )->callMemberFunction( m_functionName, finalArgs );

			if( funcRetVal.first == NULL )
			{
				//pair.second = std::shared_ptr<ksClassInstance>
				return std::static_pointer_cast< ksClassInstance >(funcRetVal.second);
			}
			else if( funcRetVal.first != NULL )
			{
				//		pair.first=hash
				//		pair.second = std::shared_ptr<void>
				if( funcRetVal.second == nullptr )
					return nullptr;
				else
				{
					return library.getType( funcRetVal.first )->createInstance( funcRetVal.second );
				}
			}
			return nullptr;
		}

		virtual int getID() const
		{
			return ksTOKEN_PRIORITY::OPERATOR_MEMBER;
		}

	};

	class ksMemberOperatorConstructor : public ksTokenConstructor
	{
	public:

		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const
		{
			if( splitCode.at( line ).second == ksRAW_TOKEN_ID::_DOT )
			{
				//no args
				if( splitCode.at( line + 3 ).second == ksRAW_TOKEN_ID::_FUNCTION_END )
				{
					auto obj = std::make_shared<ksMemberOperator>( line,
																   line + 3,
																   line + 3,
																   splitCode.at( line + 1 ).first,
																   tokenMap[line - 1],
																   std::vector<std::reference_wrapper<std::shared_ptr<ksToken>>>() );
					tokenMap[line] = obj;
					tokenMap[line + 3] = obj;//last line
					return true;
				}
				//args
				else
				{
					std::vector<std::reference_wrapper<std::shared_ptr<ksToken>>> argRefs;

					int lastLine = -1;
					// collect args
					for( int klammerCount = 1, position = 3; klammerCount > 0; position++ )
					{
						switch( splitCode[line + position].second )
						{
						case ksRAW_TOKEN_ID::_FUNCTION_BEGIN:
							klammerCount++;
							break;
						case ksRAW_TOKEN_ID::_FUNCTION_END:
							if( klammerCount == 1 )
							{
								argRefs.push_back( tokenMap[line + position] );
								lastLine = line + position;
							}
							klammerCount--;
							break;
						case ksRAW_TOKEN_ID::_KOMMA:
							if( klammerCount == 1 )
								argRefs.push_back( tokenMap[line + position] );
							break;
						}
					}

					auto obj = std::make_shared<ksMemberOperator>( line,
																   lastLine,
																   line + 2,
																   splitCode.at( line + 1 ).first,
																   tokenMap[line - 1],
																   argRefs );

					tokenMap[line] = obj;
					tokenMap[lastLine] = obj;
					return true;
				}
			}
			return false;
		}

		virtual int getPriority() const
		{
			return ksTOKEN_PRIORITY::OPERATOR_MEMBER;
		}

	};
}
