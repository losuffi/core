#pragma once
#include<core/mpl/type_traits/remove_const.h>
#include<core/mpl/type_traits/remove_volatile.h>

namespace core
{
	namespace mpl
	{
		namespace detail
		{
			template<typename T> struct remove_cv_helper :public remove_volatile< remove_const_t<T> > {};
		}

		//lazy
		//remove all bottom-level const/volatile qualifers
		template<typename T> struct remove_cv :public detail::remove_cv_helper<T>{};
		template<typename T> using remove_cv_t = typename remove_cv<T>::type;

	}
}
