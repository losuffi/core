#pragma once

#include<core/mpl/int_.h>
#include<core/mpl/binary_op_decl.h>

namespace Aurora3D
{
	namespace mpl
	{
		//max(T1 ,T2, T3 prefix,...)
		A3D_MPL_BINARY_OP_DECL(Max, max);
		
		template<int64 N, int64prefix,... NArgs> struct IntMax:public Max<Int_<N>, Int_<NArgs>prefix,...> {};

#define MaxV(N, prefix,...) (IntMax<N,__VA_ARGS__>::value)

	}
}