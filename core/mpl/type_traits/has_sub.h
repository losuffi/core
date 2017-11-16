#pragma once

#include<core/mpl/type_traits/impl/has_operator_decl.h>

namespace core
{
	namespace mpl
	{
		//test R = T::operator-(P) or R = ::operator-(T,P)
		CCDK_TT_HAS_NO_SIDE_EFFECT_BINARY_OP(- , sub);

		//test T::operator-=(P) or ::operator-=(T,P)
		CCDK_TT_HAS_SIDE_EFFECT_BINARY_OP(-, sub_assign);
	}
}