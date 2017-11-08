#pragma once

#include<core/preprocessor/impl/byte_to_uint8.h>
#include<core/preprocessor/impl/byte_add.h>
#include<core/preprocessor/impl/uint8_to_byte.h>
#include<core/preprocessor/uint8_add_one.h>
#include<core/preprocessor/uint8_shift_right.h>
#include<core/preprocessor/bool_if.h>

//x, n ranges [0,255], if x<=n        return 0
//                     if else n>=16  then call A3D_PP_BYTE_ADD
//                     else n>=0 && n<16  iterate call n times A3D_PP_ADD1
#define A3D_PP_ADD( x,n)                               \
           A3D_PP_IF(                                  \
			    A3D_PP_SHIFT_RIGHT_BOOL(n,4),          \
				A3D_PP_ADD_BYTE_IMPL,                  \
				A3D_PP_ADD_ITER_IMPL)( x, n)

//n less then 16 use 16 times ADD_one
#define  A3D_PP_ADD_ITER_IMPL( x, n)      A3D_PP_ADD_VALUE ## n(x) 
//use BYTE_ADD 
#define  A3D_PP_ADD_BYTE_IMPL( x, n)      A3D_PP_BYTE_INT( A3D_PP_BYTE_ADD(A3D_PP_INT_BYTE(x), A3D_PP_INT_BYTE(n) )) 

#define A3D_PP_ADD_VALUE0(x)     x
#define A3D_PP_ADD_VALUE1(x)     A3D_PP_ADD1(A3D_PP_ADD_VALUE0(x))
#define A3D_PP_ADD_VALUE2(x)     A3D_PP_ADD1(A3D_PP_ADD_VALUE1(x))
#define A3D_PP_ADD_VALUE3(x)     A3D_PP_ADD1(A3D_PP_ADD_VALUE2(x))
#define A3D_PP_ADD_VALUE4(x)     A3D_PP_ADD1(A3D_PP_ADD_VALUE3(x))
#define A3D_PP_ADD_VALUE5(x)     A3D_PP_ADD1(A3D_PP_ADD_VALUE4(x))
#define A3D_PP_ADD_VALUE6(x)     A3D_PP_ADD1(A3D_PP_ADD_VALUE5(x))
#define A3D_PP_ADD_VALUE7(x)     A3D_PP_ADD1(A3D_PP_ADD_VALUE6(x))
#define A3D_PP_ADD_VALUE8(x)     A3D_PP_ADD1(A3D_PP_ADD_VALUE7(x))
#define A3D_PP_ADD_VALUE9(x)     A3D_PP_ADD1(A3D_PP_ADD_VALUE8(x))
#define A3D_PP_ADD_VALUE10(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE9(x))
#define A3D_PP_ADD_VALUE11(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE10(x))
#define A3D_PP_ADD_VALUE12(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE11(x))
#define A3D_PP_ADD_VALUE13(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE12(x))
#define A3D_PP_ADD_VALUE14(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE13(x))
#define A3D_PP_ADD_VALUE15(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE14(x))
#define A3D_PP_ADD_VALUE16(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE15(x))
#define A3D_PP_ADD_VALUE17(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE16(x))
#define A3D_PP_ADD_VALUE18(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE17(x))
#define A3D_PP_ADD_VALUE19(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE18(x))
#define A3D_PP_ADD_VALUE20(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE19(x))
#define A3D_PP_ADD_VALUE21(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE20(x))
#define A3D_PP_ADD_VALUE22(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE21(x))
#define A3D_PP_ADD_VALUE23(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE22(x))
#define A3D_PP_ADD_VALUE24(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE23(x))
#define A3D_PP_ADD_VALUE25(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE24(x))
#define A3D_PP_ADD_VALUE26(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE25(x))
#define A3D_PP_ADD_VALUE27(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE26(x))
#define A3D_PP_ADD_VALUE28(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE27(x))
#define A3D_PP_ADD_VALUE29(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE28(x))
#define A3D_PP_ADD_VALUE30(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE29(x))
#define A3D_PP_ADD_VALUE31(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE30(x))
#define A3D_PP_ADD_VALUE32(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE31(x))
#define A3D_PP_ADD_VALUE33(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE32(x))
#define A3D_PP_ADD_VALUE34(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE33(x))
#define A3D_PP_ADD_VALUE35(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE34(x))
#define A3D_PP_ADD_VALUE36(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE35(x))
#define A3D_PP_ADD_VALUE37(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE36(x))
#define A3D_PP_ADD_VALUE38(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE37(x))
#define A3D_PP_ADD_VALUE39(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE38(x))
#define A3D_PP_ADD_VALUE40(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE39(x))
#define A3D_PP_ADD_VALUE41(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE40(x))
#define A3D_PP_ADD_VALUE42(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE41(x))
#define A3D_PP_ADD_VALUE43(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE42(x))
#define A3D_PP_ADD_VALUE44(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE43(x))
#define A3D_PP_ADD_VALUE45(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE44(x))
#define A3D_PP_ADD_VALUE46(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE45(x))
#define A3D_PP_ADD_VALUE47(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE46(x))
#define A3D_PP_ADD_VALUE48(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE47(x))
#define A3D_PP_ADD_VALUE49(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE48(x))
#define A3D_PP_ADD_VALUE50(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE49(x))
#define A3D_PP_ADD_VALUE51(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE50(x))
#define A3D_PP_ADD_VALUE52(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE51(x))
#define A3D_PP_ADD_VALUE53(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE52(x))
#define A3D_PP_ADD_VALUE54(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE53(x))
#define A3D_PP_ADD_VALUE55(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE54(x))
#define A3D_PP_ADD_VALUE56(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE55(x))
#define A3D_PP_ADD_VALUE57(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE56(x))
#define A3D_PP_ADD_VALUE58(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE57(x))
#define A3D_PP_ADD_VALUE59(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE58(x))
#define A3D_PP_ADD_VALUE60(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE59(x))
#define A3D_PP_ADD_VALUE61(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE60(x))
#define A3D_PP_ADD_VALUE62(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE61(x))
#define A3D_PP_ADD_VALUE63(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE62(x))
#define A3D_PP_ADD_VALUE64(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE63(x))
#define A3D_PP_ADD_VALUE65(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE64(x))
#define A3D_PP_ADD_VALUE66(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE65(x))
#define A3D_PP_ADD_VALUE67(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE66(x))
#define A3D_PP_ADD_VALUE68(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE67(x))
#define A3D_PP_ADD_VALUE69(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE68(x))
#define A3D_PP_ADD_VALUE70(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE69(x))
#define A3D_PP_ADD_VALUE71(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE70(x))
#define A3D_PP_ADD_VALUE72(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE71(x))
#define A3D_PP_ADD_VALUE73(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE72(x))
#define A3D_PP_ADD_VALUE74(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE73(x))
#define A3D_PP_ADD_VALUE75(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE74(x))
#define A3D_PP_ADD_VALUE76(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE75(x))
#define A3D_PP_ADD_VALUE77(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE76(x))
#define A3D_PP_ADD_VALUE78(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE77(x))
#define A3D_PP_ADD_VALUE79(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE78(x))
#define A3D_PP_ADD_VALUE80(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE79(x))
#define A3D_PP_ADD_VALUE81(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE80(x))
#define A3D_PP_ADD_VALUE82(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE81(x))
#define A3D_PP_ADD_VALUE83(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE82(x))
#define A3D_PP_ADD_VALUE84(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE83(x))
#define A3D_PP_ADD_VALUE85(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE84(x))
#define A3D_PP_ADD_VALUE86(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE85(x))
#define A3D_PP_ADD_VALUE87(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE86(x))
#define A3D_PP_ADD_VALUE88(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE87(x))
#define A3D_PP_ADD_VALUE89(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE88(x))
#define A3D_PP_ADD_VALUE90(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE89(x))
#define A3D_PP_ADD_VALUE91(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE90(x))
#define A3D_PP_ADD_VALUE92(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE91(x))
#define A3D_PP_ADD_VALUE93(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE92(x))
#define A3D_PP_ADD_VALUE94(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE93(x))
#define A3D_PP_ADD_VALUE95(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE94(x))
#define A3D_PP_ADD_VALUE96(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE95(x))
#define A3D_PP_ADD_VALUE97(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE96(x))
#define A3D_PP_ADD_VALUE98(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE97(x))
#define A3D_PP_ADD_VALUE99(x)    A3D_PP_ADD1(A3D_PP_ADD_VALUE98(x))
#define A3D_PP_ADD_VALUE100(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE99(x))
#define A3D_PP_ADD_VALUE101(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE100(x))
#define A3D_PP_ADD_VALUE102(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE101(x))
#define A3D_PP_ADD_VALUE103(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE102(x))
#define A3D_PP_ADD_VALUE104(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE103(x))
#define A3D_PP_ADD_VALUE105(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE104(x))
#define A3D_PP_ADD_VALUE106(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE105(x))
#define A3D_PP_ADD_VALUE107(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE106(x))
#define A3D_PP_ADD_VALUE108(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE107(x))
#define A3D_PP_ADD_VALUE109(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE108(x))
#define A3D_PP_ADD_VALUE110(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE109(x))
#define A3D_PP_ADD_VALUE111(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE110(x))
#define A3D_PP_ADD_VALUE112(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE111(x))
#define A3D_PP_ADD_VALUE113(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE112(x))
#define A3D_PP_ADD_VALUE114(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE113(x))
#define A3D_PP_ADD_VALUE115(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE114(x))
#define A3D_PP_ADD_VALUE116(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE115(x))
#define A3D_PP_ADD_VALUE117(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE116(x))
#define A3D_PP_ADD_VALUE118(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE117(x))
#define A3D_PP_ADD_VALUE119(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE118(x))
#define A3D_PP_ADD_VALUE120(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE119(x))
#define A3D_PP_ADD_VALUE121(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE120(x))
#define A3D_PP_ADD_VALUE122(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE121(x))
#define A3D_PP_ADD_VALUE123(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE122(x))
#define A3D_PP_ADD_VALUE124(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE123(x))
#define A3D_PP_ADD_VALUE125(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE124(x))
#define A3D_PP_ADD_VALUE126(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE125(x))
#define A3D_PP_ADD_VALUE127(x)   A3D_PP_ADD1(A3D_PP_ADD_VALUE126(x))