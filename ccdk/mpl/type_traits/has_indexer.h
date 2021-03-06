#pragma once 

#include<ccdk/mpl/base/logic_.h>
#include<ccdk/mpl/type_traits/is_integer.h>
#include<ccdk/mpl/type_traits/remove_dim.h>
#include<ccdk/mpl/type_traits/is_same.h>
#include<ccdk/mpl/type_traits/is_array.h>
#include<ccdk/mpl/type_traits/impl/has_operator_decl.h>

namespace ccdk
{
	namespace mpl
	{
		// defeat 
		// if define T::operator[](int) check call T::operator[](float) will get false
		// TODO : check  parameter and Ret can implicitly convert to defined function parameters

		// has_indexer<T> only for type T override operator Ret T::operator[](Index)
		HAS_MEMBER_FN_DECL(operator[], indexer);

		// type T is array or type T override operator Ret T::operator[]( Index )
		template<typename T, typename Ret, typename Index>  
		struct has_index :public or_< and_<is_array<T>, is_same<Ret, remove_dim_t<T>>, is_integer<Index>>,
			has_indexer<T,Ret,Index>>{}; 

		template<typename T, typename Ret, typename Index>
		static constexpr bool has_index_v = has_index<T, Ret, Index>::value;

	}
}