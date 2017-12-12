#include<cstdio>
#include<utility>
#include<memory>
#include<string>
#include<typeinfo>
#include<iostream>
#include<type_traits>
#include<cassert>
#include<functional>
#include<ccdk/mpl/type_traits.h>
#include<ccdk/mpl/base/arg_pack.h>
#include<ccdk/mpl/base/val_pack.h>
#include<ccdk/mpl/base/integer_.h>
#include<ccdk/mpl/base/int_.h>
#include<ccdk/mpl/function/arg.h>
#include<ccdk/mpl/function/function.h>
#include<ccdk/mpl/function/bind_mfn.h>
#include<ccdk/mpl/function/partial.h>
#include<ccdk/mpl/function/capture.h>
#include<ccdk/mpl/function/combine.h>
#include<ccdk/mpl/function/dispatch.h>
#include<ccdk/mpl/function/fmap.h>
#include<ccdk/mpl/type_traits/select_case.h>
#include<ccdk/mpl/function/placeholder.h>
#include<ccdk/mpl/container/ref_tuple.h>
#include<ccdk/mpl/base/sfinae.h>


using namespace ccdk;
using namespace ccdk::mpl;
using namespace ccdk::mpl::fn;
using namespace ccdk::mpl::placeholder;
using namespace ccdk::mpl::literals;


template<typename T, typename = void> struct test_when :test_when<T, when > {};
template<typename T, bool condi>    struct test_when<T, match_default<condi> > { static constexpr int value = 1; };
template<typename T> struct test_when<T, match< is_void<T>> > { static constexpr int value = 2; };
template<typename T> struct test_when<T, match_one< is_float<T>, is_integer<T> >> { static constexpr int value = 3; };
template<typename T> struct test_when<T, match_both< is_top_const<T>, is_pointer<T> >> { static constexpr int value = 4; };
template<typename T> static constexpr int test_when_v = test_when<T>::value;

template<typename T>
void fn_impl(case_t< is_function >, T&& t)
{
	DebugValue("is function");
}

template<typename T>
void fn_impl(case_t< is_function_ptr>, T&& t)
{
	DebugValue("is function pointer");
}

template<typename T>
void fn_impl(case_t< is_function_obj>, T&& t)
{
	DebugValue("is function obj");
}

template<typename T>
void fn_impl(case_t< is_mfn_ptr>, T&&t)
{
	DebugValue("is member function");
}

template<typename T>
void fn_impl(default_t, T&& t)
{
	DebugValue("default function ");
}

template<typename T>
void fn_impl(case_or<is_float, is_integer >, T&& t)
{
	DebugValue("is integer/float ");
}

template<typename T>
void fn_impl(case_and<is_pointer, is_void >, T&& t)
{
	DebugValue("is void* ");
}

template<typename T, typename P = remove_ref_t<T>>
void fn_select_test(T&& t)
{
	::fn_impl(
		select_case<
			is_function<P>,
			is_function_ptr<P>,
			is_function_obj<P>,
			is_mfn_ptr<P>,
			or_<is_float<P>, is_integer<P>>,
			and_< is_pointer<P>, is_void<remove_pointer_t<P>>>
		>,
		util::forward<T>(t)
	);
}

void simple_nfn() {}

struct test_obj
{
	int operator()(test_copy_t& tt, float a)
	{
		DebugValue(a);
		return 0;
	}
};




template<typename T>
void test_tmp(T&& t)
{
	T tt{ t };
	DebugTypeName<T>();
	DebugTypeName<decltype(t)>();
	DebugTypeName<decltype(util::forward<T>(t))>();
	DebugTypeName<decltype(tt)>();
}

int call1(int a, const char*msg)
{
	DebugValue(msg);
	return a;
}

int call2(int a)
{
	return a;
}

int call3(int a)
{
	return a;
}


struct base
{
	virtual void test_size()
	{
		DebugValue("base");
	}
	virtual ~base()
	{
		DebugValue("base destructor");
	}
};

struct derive :public base
{
	virtual void test_size() override
	{
		DebugValue("derive");
	}

	virtual ~derive() override
	{
		DebugValue("derive destructor");
	}
};



struct change_t {
	void change() 
	{
		a = 1;
	}
	int a = 0;
};

template<typename T>
auto test_const(const T& t)
{
	return T{ const_cast<T&&>(t) };
}


void test(int a) noexcept
{
	DebugValue(a);

}

void test(int a, int b)
{
	DebugValue(b);
}



template<typename T, typename... Args>
struct is_invocable
{
	template<typename U, typename P = decltype( declval<U>()( declval<Args>()... ) )>
	static constexpr bool sfinae(int) { return true; }

	template<typename U>
	static constexpr bool sfinae(...) { return false; }

	static constexpr bool value = sfinae<T>(0);
};

struct TT
{
	auto operator[](int)
	{

	}
	auto operator()(int)
	{
		return 0;
	}

	auto operator()(int, int)
	{
		return 0;
	}

	auto invoke(int)
	{
		return 0;
	}
};

int test_inc2(int a) noexcept
{
	return a + 1;
}

template<typename T1, typename T2>
auto test_tmp(T1&& t1, T2&& t2)
{
	return t1 + t2;
}

int main()
{ 
	void(*test_ptr)(int, int) = test;
	typedef decltype(test_ptr) test_fn;
	DebugValue(is_invocable<test_fn, int>::value);
	DebugValue(is_invocable<int, int>::value);
	DebugValue(is_invocable<TT, int>::value);

	DebugNewTitle("test invoker");
	DebugValue(has_invoker_v<TT, null_, int,int>);
	DebugValue(has_invoker_v<TT, null_, int>);
	DebugValue(has_invoker_v<TT>);
	DebugValue(has_invoker_v<test_copy_t>);


	int (TT::*mfn_ptr)(int,int) = &TT::operator();
	using test_mfn = decltype(mfn_ptr);
	DebugValue(is_invocable<TT, int, int>::value);
	DebugValue(is_invocable<test_mfn, int>::value);
	DebugValue(is_invocable<test_mfn, int, int>::value);
	
	

	test_copy_t tt{};
	const test_copy_t ctt;
	constexpr test_constexpr_t cxtt;

	DebugNewTitle("test when dispatch");
	AssertTrue(test_when_v<int> == 3);
	AssertTrue(test_when_v<float> == 3);
	AssertTrue(test_when_v<void> == 2);
	AssertTrue(test_when_v<const int*> == 4);
	AssertTrue(test_when_v<nullptr_t> == 1);

	DebugNewTitle("function static dispatch");
	fn_select_test(0);
	fn_select_test(simple_nfn);
	fn_select_test(&simple_nfn);
	fn_select_test(test_obj{});
	fn_select_test(&test_obj::operator());
	fn_select_test(1);
	fn_select_test(1.2f);
	fn_select_test((void*)0);

	DebugNewTitle("bind member function");
	auto mfn1 = bind_mfn(&test_copy_t::test_mfn, tt);
	auto mfn2 = bind_mfn(&test_copy_t::test_mfn, ctt);
	auto mfn3 = bind_mfn(&test_copy_t::test_mfn, &tt);
	auto mfn4 = bind_mfn(&test_copy_t::test_mfn, &ctt);
	mfn1(1, "bind mfn1 ");
	mfn2(2, "bind mfn2 ");
	mfn3(3, "bind mfn3 ");
	mfn4(4, "bind mfn4 ");

	DebugNewTitle("test partial");
	DebugSubTitle("function object");
	partial(tt, 1)(" hello,partial copy object");
	partial(util::move(tt), 1)(" hello,partial move object");
	
	DebugSubTitle("function/function pointer");
	partial(test_normal_copy_function, util::move(tt))("hello,partial function");
	partial(test_normal_move_function, util::move(tt))("hello,partial function");
	partial(&test_normal_copy_function, util::move(tt))("hello,partial function");
	partial(&test_normal_move_function, util::move(tt))("hello,partial function");
	partial(test_normal_copy_function, tt)("hello,partial function");
	partial(test_normal_move_function, tt)("hello,partial function");
	partial(&test_normal_copy_function, tt)("hello,partial function");
	partial(&test_normal_move_function, tt)("hello,partial function");
	DebugSubTitle("member function pointer");
	partial(&test_copy_t::test_mfn, tt)(2, "hello, 2 partial  obj member function");
	partial(&test_copy_t::test_mfn, &tt)(2, "hello, 2 partial pointer member function");
	partial(&test_copy_t::test_mfn, tt)(2)("hello, 3 partial  obj member function");


	DebugNewTitle("combine");
	//1+1+2+3+4
	struct test_combine_mfn { int operator()(int a) { return a + 3; } int inc3(int a) { return a + 4;} };
	test_combine_mfn tcm{};
	DebugValue( combine(op::inc, op::inc, test_inc2, test_combine_mfn{}, bind_mfn(&test_combine_mfn::inc3, tcm) )(1));
	constexpr auto a =  combine(op::inc, op::inc);

	DebugNewTitle("dispatch");
	DebugValue(dispatch(op::add, op::inc, op::inc)(1,2));
	
	DebugNewTitle("fmap");
	DebugValue(fmap(op::mul, op::add, op::sub)(4, 1));



	getchar();
	return 0;


	
	

	///*DebugNewTitle("test function");
	//function<void(test_copy_t&, const char*)> nfn1{ test_normal_function };
	//nfn1(tt, "normal function invoke");*/
	//DebugNewTitle("test combine");
	//auto cb1 = combine(call1, call2, call3);
	//DebugValue(cb1(3, "hello,combine"));
	//DebugNewTitle("test capture");
	//auto cap1 = capture(4)(call1);
	//DebugValue(cap1("hello, capture"));

	getchar();
	return 0;
}