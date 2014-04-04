//_______FUNCTION_______//

#include "stdafx.h"

namespace kg
{
	template <std::size_t...> struct index_sequence
	{ };

	template <std::size_t N, std::size_t... Is>
	struct make_index_sequence : make_index_sequence<N - 1, N - 1, Is...>
	{ };

	template <std::size_t... Is>
	struct make_index_sequence<0u, Is...> : index_sequence<Is...>{ };


	template<typename F> class FunctionWrapper;


	//NON MEMBER FUNCTION
	//FunctionWrapper<decltype(foo)> wrapper( foo );
	template<class Ret, typename ... Args>
	class FunctionWrapper<Ret( Args... )>
	{
		typedef std::function<Ret( Args... )> FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		void call( const std::vector<std::shared_ptr<void>>& args,
				   index_sequence<Is...> )
		{
			m_function( *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... );
		}
	public:
		FunctionWrapper( const FuncContainer& func ) : m_function( func )
		{ }

		void call( const std::vector<std::shared_ptr<void>>& args )
		{
			assert( args.size() == sizeof...(Args) );
			call( args, make_index_sequence<sizeof...(Args)>() );
		}

	};

	//MEMBER FUNCTION
	//FunctionWrapper<decltype(&Foo::foo)> wrapper( &Foo::foo );
	template<class Obj, class Ret, typename ... Args>
	class FunctionWrapper<Ret( Obj::* )(Args...)>
	{
		typedef Ret( Obj::*FuncPasser )(Args...);
		typedef std::function< Ret( Obj&, Args... ) > FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		void call( std::shared_ptr<void>& obj,
				   const std::vector<std::shared_ptr<void>>& args,
				   index_sequence<Is...> )
		{
			m_function( *static_cast< Obj* >(obj.get()), *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... );
		}
	public:
		//std::mem_fn( func ) is used to bypass a VisualStudio bug
		FunctionWrapper( const FuncPasser& func ) : m_function( std::mem_fn( func ) )
		{ }

		void call( std::shared_ptr<void>& obj,
				   const std::vector<std::shared_ptr<void>>& args )
		{
			assert( args.size() == sizeof...(Args) );
			call( obj, args, make_index_sequence<sizeof...(Args)>() );
		}

	};
}