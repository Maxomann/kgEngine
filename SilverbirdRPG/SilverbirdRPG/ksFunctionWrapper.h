//_______FUNCTION_WRAPPER_______//

#pragma once
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


	class ksFunctionWrapperInterface
	{
	public:
		virtual void call( const std::vector<std::shared_ptr<void>>& args )const = 0;
		virtual size_t getSignatureHash()const=0;
		virtual const std::string getSignature()const = 0;
	};
	class ksMemberFunctionWrapperInterface
	{
	public:
		virtual void call( std::shared_ptr<void>& obj,
						   const std::vector<std::shared_ptr<void>>& args )const = 0;
		virtual size_t getSignatureHash()const = 0;
		virtual const std::string getSignature()const = 0;
	};


	template<typename F> class ksFunctionWrapper;

	//NON MEMBER FUNCTION
	//FunctionWrapper<decltype(foo)> wrapper( foo );
	template<class Ret, typename ... Args>
	class ksFunctionWrapper<Ret( Args... )> : public ksFunctionWrapperInterface
	{
		typedef std::function<Ret( Args... )> FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		void call( const std::vector<std::shared_ptr<void>>& args,
				   index_sequence<Is...> )const
		{
			m_function( *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... );
		}
	public:
		ksFunctionWrapper( const FuncContainer& func ) : m_function( func )
		{ }

		void call( const std::vector<std::shared_ptr<void>>& args )const
		{
			assert( args.size() == sizeof...(Args) );
			call( args, make_index_sequence<sizeof...(Args)>() );
		}

		virtual size_t getSignatureHash() const
		{
			return typeid(m_function).hash_code();
		}

		virtual const std::string getSignature() const
		{
			return typeid(m_function).name();
		}

	};

	//MEMBER FUNCTION
	//FunctionWrapper<decltype(&Foo::foo)> wrapper( &Foo::foo );
	template<class Obj, class Ret, typename ... Args>
	class ksFunctionWrapper<Ret( Obj::* )(Args...)> : public ksMemberFunctionWrapperInterface
	{
		typedef Ret( Obj::*FuncPasser )(Args...);
		typedef std::function< Ret( Obj&, Args... ) > FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		void call( std::shared_ptr<void>& obj,
				   const std::vector<std::shared_ptr<void>>& args,
				   index_sequence<Is...> )const
		{
			m_function( *static_cast< Obj* >(obj.get()), *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... );
		}
	public:
		//std::mem_fn( func ) is used to bypass a VisualStudio bug
		ksFunctionWrapper( const FuncPasser& func ) : m_function( std::mem_fn( func ) )
		{ }

		void call( std::shared_ptr<void>& obj,
				   const std::vector<std::shared_ptr<void>>& args )const
		{
			assert( args.size() == sizeof...(Args) );
			call( obj, args, make_index_sequence<sizeof...(Args)>() );
		}

		virtual size_t getSignatureHash() const
		{
			return typeid(m_function).hash_code();
		}

		virtual const std::string getSignature() const
		{
			return typeid(m_function).name();
		}

	};
}