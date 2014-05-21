//_______ksFunctionCall_______//

#pragma once
#include "ksToken.h"
#include "ksLibrary.h"

namespace kg
{
	class ksFunctionCall : public ksToken
	{
		const std::string m_functionName;
		const std::vector<std::reference_wrapper<std::shared_ptr<ksToken>>> m_args;

	public:
		ksFunctionCall( int firstLineOfToken,
						int lastLineOfToken,
						int lastLineWhileConstruction,
						const std::string& functionName,
						const std::vector<std::reference_wrapper<std::shared_ptr<ksToken>>> args )
						: ksToken( firstLineOfToken, lastLineOfToken, lastLineWhileConstruction ),
						m_functionName( functionName ),
						m_args( args )
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

			auto funcRetVal = library.getFunction( m_functionName )->call( library, finalArgs );

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
		}

		virtual int getID() const
		{
			return ksTOKEN_PRIORITY::FUNCTION_CALL;
		}

	};

	class ksFunctionCallConstructor : public ksTokenConstructor
	{
	public:

		virtual bool construct( const ksTokenConstructorPriorityMap& tokenConstructors,
								const ksSplitCodeVector& splitCode,
								ksTokenMap& tokenMap,
								int line ) const
		{
			if( splitCode.at( line ).second == ksRAW_TOKEN_ID::_FUNCTION_BEGIN )
			{
				if( splitCode.at( line - 1 ).second == ksRAW_TOKEN_ID::_IDENTIFIER )
				{
					//no args
					if( splitCode.at( line + 1 ).second == ksRAW_TOKEN_ID::_FUNCTION_END )
					{
						auto obj = std::make_shared<ksFunctionCall>( line - 1,
																	 line + 1,
																	 line + 1,
																	 splitCode.at( line - 1 ).first,
																	 std::vector<std::reference_wrapper<std::shared_ptr<ksToken>>>() );
						tokenMap[line - 1] = obj;
						tokenMap[line] = obj;
						return true;
					}
					//args
					else
					{
						std::vector<std::reference_wrapper<std::shared_ptr<ksToken>>> argRefs;

						int lastLine=-1;
						// collect args
						for( int klammerCount = 1, position = 1; klammerCount > 0; position++ )
						{
							switch( splitCode[line + position].second )
							{
							case ksRAW_TOKEN_ID::_FUNCTION_BEGIN:
								klammerCount++;
								break;
							case ksRAW_TOKEN_ID::_FUNCTION_END:
								if( klammerCount == 1 )
								{
									argRefs.push_back( tokenMap[line + position - 1] );
									lastLine = line + position;
								}
								klammerCount--;
								break;
							case ksRAW_TOKEN_ID::_KOMMA:
								if( klammerCount == 1 )
									argRefs.push_back( tokenMap[line + position - 1] );
								break;
							}
						}

						auto obj = std::make_shared<ksFunctionCall>( line - 1,
																	 lastLine,
																	 line,
																	 splitCode.at( line - 1 ).first,
																	 argRefs );

						tokenMap[line - 1] = obj;
						tokenMap[line] = obj;
						return true;
					}
				}
			}

			return false;
		}

		virtual int getPriority() const
		{
			return ksTOKEN_PRIORITY::FUNCTION_CALL;
		}

	};
}
