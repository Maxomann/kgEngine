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
		virtual std::pair<size_t, std::shared_ptr<void>> call( const std::vector<std::shared_ptr<void>>& args )const = 0;
		virtual size_t getSignatureHash()const = 0;
		virtual const std::string getSignature()const = 0;
	};
	class ksMemberFunctionWrapperInterface
	{
	public:
		virtual std::pair<size_t, std::shared_ptr<void>> call( const std::shared_ptr<void>& obj,
															   const std::vector<std::shared_ptr<void>>& args )const = 0;
		virtual size_t getSignatureHash()const = 0;
		virtual const std::string getSignature()const = 0;
	};


	template<typename F> class ksFunctionWrapper;

	//NON MEMBER FUNCTION
	//FunctionWrapper<decltype(foo)> wrapper( foo );
	// Returning POINTERS in wrapped function is NOT ALLOWED
	template<class Ret, typename ... Args>
	class ksFunctionWrapper<Ret( Args... )> : public ksFunctionWrapperInterface
	{
		typedef std::function<Ret( Args... )> FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		std::pair<size_t, std::shared_ptr<void>> call( const std::vector<std::shared_ptr<void>>& args,
													   index_sequence<Is...> )const
		{
			auto retVal = std::make_shared<Ret>( m_function( *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... ) );
			return std::make_pair( typeid(Ret).hash_code(), retVal );
		}
	public:
		ksFunctionWrapper( const FuncContainer& func ) : m_function( func )
		{ }

		std::pair<size_t, std::shared_ptr<void>> call( const std::vector<std::shared_ptr<void>>& args )const
		{
			assert( args.size() == sizeof...(Args) );
			return call( args, make_index_sequence<sizeof...(Args)>() );
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
	// Returning POINTERS in wrapped function is NOT ALLOWED
	template<class Obj, class Ret, typename ... Args>
	class ksFunctionWrapper<Ret( Obj::* )(Args...)> : public ksMemberFunctionWrapperInterface
	{
		typedef Ret( Obj::*FuncPasser )(Args...);
		typedef std::function< Ret( Obj&, Args... ) > FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		std::pair<size_t, std::shared_ptr<void>> call( const std::shared_ptr<void>& obj,
													   const std::vector<std::shared_ptr<void>>& args,
													   index_sequence<Is...> )const
		{
			auto retVal = std::make_shared<Ret>( m_function( *static_cast< Obj* >(obj.get()), *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... ) );
			return std::make_pair( typeid(Ret).hash_code(), retVal );
		}
	public:
		//std::mem_fn( func ) is used to work around a VisualStudio bug
		ksFunctionWrapper( const FuncPasser& func ) : m_function( std::mem_fn( func ) )
		{ }
		ksFunctionWrapper( const FuncContainer& func ) :m_function( func )
		{ }

		std::pair<size_t, std::shared_ptr<void>> call( const std::shared_ptr<void>& obj,
													   const std::vector<std::shared_ptr<void>>& args )const
		{
			assert( args.size() == sizeof...(Args) );
			return call( obj, args, make_index_sequence<sizeof...(Args)>() );
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



	// NON MEMBER FUNCTION
	// RETURN_TYPE: void
	// FunctionWrapper<decltype(foo)> wrapper( foo );
	// Returning POINTERS in wrapped function is NOT ALLOWED
	template<typename ... Args>
	class ksFunctionWrapper<void( Args... )> : public ksFunctionWrapperInterface
	{
		typedef std::function<void( Args... )> FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		std::pair<size_t, std::shared_ptr<void>> call( const std::vector<std::shared_ptr<void>>& args,
													   index_sequence<Is...> )const
		{
			m_function( *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... );
			return std::make_pair( typeid(void).hash_code(), std::shared_ptr<void>() );
		}
	public:
		ksFunctionWrapper( const FuncContainer& func ) : m_function( func )
		{ }

		std::pair<size_t, std::shared_ptr<void>> call( const std::vector<std::shared_ptr<void>>& args )const
		{
			assert( args.size() == sizeof...(Args) );
			return call( args, make_index_sequence<sizeof...(Args)>() );
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

	// MEMBER FUNCTION
	// RETURN_TYPE: void
	// FunctionWrapper<decltype(&Foo::foo)> wrapper( &Foo::foo );
	// Returning POINTERS in wrapped function is NOT ALLOWED
	template<class Obj, typename ... Args>
	class ksFunctionWrapper<void( Obj::* )(Args...)> : public ksMemberFunctionWrapperInterface
	{
		typedef void( Obj::*FuncPasser )(Args...);
		typedef std::function< void( Obj&, Args... ) > FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		std::pair<size_t, std::shared_ptr<void>> call( const std::shared_ptr<void>& obj,
													   const std::vector<std::shared_ptr<void>>& args,
													   index_sequence<Is...> )const
		{
			m_function( *static_cast< Obj* >(obj.get()), *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... );
			return std::make_pair( typeid(void).hash_code(), std::shared_ptr<void>() );
		}
	public:
		//std::mem_fn( func ) is used to work around a VisualStudio bug
		ksFunctionWrapper( const FuncPasser& func ) : m_function( std::mem_fn( func ) )
		{ }
		ksFunctionWrapper( const FuncContainer& func ) :m_function( func )
		{ }

		std::pair<size_t, std::shared_ptr<void>> call( const std::shared_ptr<void>& obj,
													   const std::vector<std::shared_ptr<void>>& args )const
		{
			assert( args.size() == sizeof...(Args) );
			return call( obj, args, make_index_sequence<sizeof...(Args)>() );
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


	// CONST MEMBER FUNCTION
	// FunctionWrapper<decltype(&Foo::foo)> wrapper( &Foo::foo );
	// Returning POINTERS in wrapped function is NOT ALLOWED
	template<class Obj, class Ret, typename ... Args>
	class ksFunctionWrapper<Ret( Obj::* )(Args...)const> : public ksMemberFunctionWrapperInterface
	{
		typedef Ret( Obj::*FuncPasser )(Args...)const;
		typedef std::function< Ret( Obj&, Args... ) > FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		std::pair<size_t, std::shared_ptr<void>> call( const std::shared_ptr<void>& obj,
													   const std::vector<std::shared_ptr<void>>& args,
													   index_sequence<Is...> )const
		{
			auto retVal = std::make_shared<Ret>( m_function( *static_cast< Obj* >(obj.get()), *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... ) );
			return std::make_pair( typeid(Ret).hash_code(), retVal );
		}
	public:
		//std::mem_fn( func ) is used to work around a VisualStudio bug
		ksFunctionWrapper( const FuncPasser& func ) : m_function( std::mem_fn( func ) )
		{ }
		ksFunctionWrapper( const FuncContainer& func ) :m_function( func )
		{ }

		std::pair<size_t, std::shared_ptr<void>> call( const std::shared_ptr<void>& obj,
													   const std::vector<std::shared_ptr<void>>& args )const
		{
			assert( args.size() == sizeof...(Args) );
			return call( obj, args, make_index_sequence<sizeof...(Args)>() );
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

	// MEMBER FUNCTION
	// RETURN_TYPE: void
	// FunctionWrapper<decltype(&Foo::foo)> wrapper( &Foo::foo );
	// Returning POINTERS in wrapped function is NOT ALLOWED
	template<class Obj, typename ... Args>
	class ksFunctionWrapper<void(Obj::*)(Args...)const> : public ksMemberFunctionWrapperInterface
	{
		typedef void(Obj::*FuncPasser)(Args...)const;
		typedef std::function< void( Obj&, Args... ) > FuncContainer;
		const FuncContainer m_function;

		template <std::size_t ... Is>
		std::pair<size_t, std::shared_ptr<void>> call( const std::shared_ptr<void>& obj,
													   const std::vector<std::shared_ptr<void>>& args,
													   index_sequence<Is...> )const
		{
			m_function( *static_cast< Obj* >(obj.get()), *static_cast< typename std::remove_reference<Args...>::type* >(args.at( Is ).get())... );
			return std::make_pair( typeid(void).hash_code(), std::shared_ptr<void>() );
		}
	public:
		//std::mem_fn( func ) is used to work around a VisualStudio bug
		ksFunctionWrapper( const FuncPasser& func ) : m_function( std::mem_fn( func ) )
		{ }
		ksFunctionWrapper( const FuncContainer& func ) :m_function( func )
		{ }

		std::pair<size_t, std::shared_ptr<void>> call( const std::shared_ptr<void>& obj,
													   const std::vector<std::shared_ptr<void>>& args )const
		{
			assert( args.size() == sizeof...(Args) );
			return call( obj, args, make_index_sequence<sizeof...(Args)>() );
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