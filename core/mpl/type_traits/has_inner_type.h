#pragma once

#include<core/mpl/type_traits/impl/has_operator_type.h>
#include<core/mpl/type_traits/impl/has_inner_decl.h>
#include<core/mpl/base/bool_.h>

namespace core
{
	namespace mpl
	{
		//test if T::type is well-formed
		A3D_TT_HAS_INNER_DECL(type, type);

		//test if T::value_type is well-formed
		A3D_TT_HAS_INNER_DECL(value_type, value_type);
	}
}