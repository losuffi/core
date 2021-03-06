#pragma once

#include<ccdk/mpl/type_traits/impl/has_operator_decl.h>

namespace ccdk
{
	namespace mpl
	{
		//test R = T::operator%(P) or R = ::operator%(T,P)
		CCDK_TT_HAS_NO_SIDE_EFFECT_BINARY_OP(% , mod);

		//test T::operator%=(P) or ::operator%=(T,P)
		CCDK_TT_HAS_SIDE_EFFECT_BINARY_OP(%=, mod_assign);
	}
}