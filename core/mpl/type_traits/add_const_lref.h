#pragma once

#include<core/mpl/type_traits/is_void.h>
#include<core/mpl/type_traits/add_top_const.h>
#include<core/mpl/type_traits/add_lref.h>
#include<core/mpl/type_traits/remove_pointer.h>

namespace core
{
	namespace mpl
	{
		//void => void
		//NonMemberFunction => NonMemberFunction
		//T    => const T&
		//T&   => const T&
		//T&&  => const T&
		//T*   => const T&
		namespace detail
		{ 
			template<typename T, bool isVoid = is_void_v<T> > struct add_const_lref_helper { typedef add_top_const_t< add_lref_t< remove_pointer_t<T>>> type; };
			template<typename T> struct add_const_lref_helper<T, true> { typedef void type; };
		}

		//lazy force convert to const T& form
		template<typename T> struct add_const_lref :public detail::add_const_lref_helper<T> {};
		template<typename T> using add_const_lref_t = typename add_const_lref<T>::type;
	}
}