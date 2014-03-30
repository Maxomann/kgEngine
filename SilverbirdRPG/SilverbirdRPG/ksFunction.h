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



	template<typename F> class MemberFunctionWrapper;

	template<class Obj, class Ret, typename ... Args>
	class MemberFunctionWrapper<Ret( Obj::* )(Args...)>
	{
		typedef Ret( Obj::*MemberFunction )(Args...);
		const MemberFunction m_memberfunction;

		template <std::size_t ... Is>
		void call( std::shared_ptr<void>& obj,
				   const std::vector<std::shared_ptr<void>>& args,
				   index_sequence<Is...> )
		{
			(static_cast< Obj* >(obj.get())->*m_memberfunction)
				(*static_cast< typename std::remove_reference<Args>::type* >(args.at( Is ).get())...);
		}
	public:
		MemberFunctionWrapper( MemberFunction memFn ) : m_memberfunction( memFn )
		{ }

		void call( std::shared_ptr<void>& obj,
				   const std::vector<std::shared_ptr<void>>& args )
		{
			assert( args.size() == sizeof...(Args) );
			call( obj, args, make_index_sequence<sizeof...(Args)>() );
		}

	};
}