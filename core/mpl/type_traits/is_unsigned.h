#pragma once

#include<core/mpl/base/bool_.h>
#include<core/mpl/base/and_.h>
#include<core/mpl/type_traits/is_integral.h>

namespace core
{
	namespace mpl
	{
		namespace detail
		{
			template<typename T>
			struct is_unsigned_helper :public bool_< (T(0) < T(-1)) >{};
		}

		template<typename T> struct is_unsigned :
			public and_< is_integer<T>, detail::is_unsigned_helper<T> > {};
		template<typename T> constexpr bool is_unsigned_v = is_unsigned<T>::value;
	}
}