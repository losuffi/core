#pragma once

#include<ccdk/mpl/mpl_module.h>
#include<ccdk/mpl/type_traits/remove_ref.h>

ccdk_namespace_mpl_util_start

/* T&& forward string literial will become char array ref
   int literial will become int&
 */
template<typename T> 
CCDK_FORCEINLINE constexpr T&& forward(remove_ref_t<T>& t) noexcept { 
	return static_cast<T&&>(t); 
}

template<typename T> 
CCDK_FORCEINLINE constexpr T&& forward(remove_ref_t<T>&& t) noexcept { 
	return static_cast<T&&>(t); 
}

ccdk_namespace_mpl_util_end