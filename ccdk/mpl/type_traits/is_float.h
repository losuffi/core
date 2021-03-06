#pragma once

#include<ccdk/mpl/base/type_.h>
#include<ccdk/mpl/type_traits/traits_case.h>

namespace ccdk
{
	namespace mpl
	{
		template<typename T> struct is_float :public false_{};
		template<> struct is_float<float> :public  true_ {};
		template<> struct is_float<double> :public true_ {};
		template<> struct is_float<long double> :public true_ {};
		template<typename T> struct is_float<T const> :public is_float<T> {};
		template<typename T> struct is_float<T volatile> :public is_float<T> {};
		template<typename T> struct is_float<T const volatile> :public is_float<T> {};


		template<typename T> constexpr bool is_float_v = is_float<T>::value;

		CCDK_TT_SINGLE_RANK(is_float);
	}
}
