#pragma once

#include<ccdk/mpl/mpl_module.h>
#include<ccdk/mpl/base/enable_if.h>
#include<ccdk/mpl/base/not_.h>
#include<ccdk/mpl/base/and_.h>
#include<ccdk/mpl/base/or_.h>
#include<ccdk/mpl/type_traits/is_void.h>
#include<ccdk/mpl/type_traits/is_class.h>
#include<ccdk/mpl/type_traits/is_union.h>
#include<ccdk/mpl/type_traits/is_array.h>
#include<ccdk/mpl/type_traits/is_pod.h>
#include<ccdk/mpl/type_traits/is_same.h>
#include<ccdk/mpl/type_traits/identity.h>
#include<ccdk/mpl/type_traits/is_convertible.h>
#include<ccdk/mpl/type_traits/remove_dim.h>
#include<ccdk/mpl/util/noncopyable.h>
#include<ccdk/mpl/util/swap.h>
#include<ccdk/mpl/util/value.h>
#include<ccdk/mpl/util/hash.h>
#include<ccdk/mpl/util/compatible_cmp.h>
#include<ccdk/mpl/smart_ptr/smart_ptr_fwd.h>
#include<ccdk/mpl/smart_ptr/default_deleter.h>
#include<ccdk/mpl/smart_ptr/default_ref_count.h>


ccdk_namespace_mpl_sp_start

//static small and simple share_ptr implements, Deleter / RefCount / Allocator ensure at compile time


template<
	typename T,
	typename Deleter,   //normal deleter for different type
	typename RefCount  // multi-thread need atomic ref_count
>
class share_ptr_base
{
public:
	typedef remove_dim_t<T>                      value_type;
	typedef value_type*					         pointer_type;
	typedef Deleter						         delete_type;
	typedef RefCount					         ref_count_type;
	typedef share_ptr_base				         this_type;
	typedef weak_ptr<T, Deleter, RefCount>       weak_type;
	template<typename, typename, typename> friend class share_ptr_base;
	template<typename, typename, typename> friend class weak_ptr;
protected:
	ref_count_type*     ref_count;
	pointer_type        content;

public:

	//default constructor
	CCDK_FORCEINLINE share_ptr_base() noexcept :ref_count{ nullptr }, content{ nullptr } {}
	//nullptr constructor
	CCDK_FORCEINLINE share_ptr_base(ptr::nullptr_t) noexcept : ref_count{ nullptr }, content{ nullptr } {}

	//construct from T pointer, new may throw( bad_alloc) but no need process just spread out
	CCDK_FORCEINLINE explicit share_ptr_base(pointer_type ptr) : ref_count{ new RefCount{ 1,1 } }, content{ ptr } {}
	//construct from weak_ptr
	CCDK_FORCEINLINE explicit share_ptr_base(const weak_type& wp) noexcept : ref_count{ wp.ref_count }, content{ wp.ptr } { if (ref_count) ref_count->inc_share_count(); }

	//copy constructor
	CCDK_FORCEINLINE share_ptr_base(const share_ptr_base& other) noexcept : ref_count{ other.ref_count }, content{ other.content } { if (ref_count) ref_count->inc_share_count(); }
	template< typename T2, typename D2, typename R2, typename = check_t< is_convertible< share_ptr_base<T2, D2, R2>, this_type >> >
	CCDK_FORCEINLINE share_ptr_base(const share_ptr_base<T2, D2, R2> & other) noexcept : ref_count{ other.ref_count }, content{ other.content } { if (ref_count) ref_count->inc_share_count(); }

	//move constructor
	template< typename T2, typename D2, typename R2, typename = check_t< is_convertible< share_ptr<T2, D2, R2>, this_type >> >
	CCDK_FORCEINLINE share_ptr_base(share_ptr_base<T2, D2, R2>&& other) noexcept : ref_count{ other.ref_count }, content{ other.content } {}

	//value assign, may throw
	CCDK_FORCEINLINE share_ptr_base& operator=(pointer_type ptr) { share_ptr_base{ ptr }.swap(*this); return *this; }

	//copy assign, protect from self assign, may throw when front content destruct 
	CCDK_FORCEINLINE share_ptr_base& operator=(const share_ptr_base& other) { if (ccdk_likely(util::addressof(other) != this)) { share_ptr_base{ other }.swap(*this); } return *this; }
	template< typename T2, typename D2, typename R2, typename = check_t< is_convertible< share_ptr_base<T2, D2, R2>, this_type >> >
	CCDK_FORCEINLINE share_ptr_base& operator=(const share_ptr_base<T2, D2, R2>& other) {   share_ptr_base{ other }.swap(*this); return *this; }

	//move assign, protect from self assign, may throw when front content destruct 
	CCDK_FORCEINLINE share_ptr_base& operator=(share_ptr_base&& other) { if (ccdk_likely(util::addressof(other) != this)) { share_ptr_base{ util::move(other) }.swap(*this); } return *this; }
	template< typename T2, typename D2, typename R2, typename = check_t< is_convertible< share_ptr_base<T2, D2, R2>, this_type >> >
	CCDK_FORCEINLINE share_ptr_base& operator=(share_ptr_base<T2, D2, R2>&& other) { share_ptr_base{ util::move(other) }.swap(*this); return *this; }

	//swap operation
	template< typename T2, typename D2, typename R2, typename = check_t< is_convertible< share_ptr_base<T2, D2, R2>, this_type >> >
	CCDK_FORCEINLINE void swap(share_ptr_base<T2, D2, R2>& other) noexcept { util::swap(ref_count, other.ref_count); util::swap(content, other.content); }

	//get pointer
	CCDK_FORCEINLINE pointer_type pointer() const noexcept { return content; }

	//share count
	CCDK_FORCEINLINE uint32 share_count() const noexcept { return ref_count->share_count; }

	//destructor
	CCDK_FORCEINLINE ~share_ptr_base() { if (ref_count) ref_count->dec_share_count(Deleter{}, content); /*not store Deleter*/ }
};


//for non-array, non-void, non-thread-safe implements
// have member operation
// have dereference operation
// no   index operation
template<
	typename T,
	typename Deleter =  default_deleter<T>,     //normal deleter for different type
	typename RefCount = default_ref_count<uint32>  // multi-thread need atomic ref_count, need nothrow constructor
>
class share_ptr: public share_ptr_base<T,Deleter, RefCount>
{ 
public:
	typedef  share_ptr_base<T, Deleter, RefCount> base_type;
	typedef typename base_type::value_type        value_type;

	//base constructor
	using base_type::base_type;
	using base_type::operator=;
	using base_type::swap;
	using base_type::share_count;
	using base_type::pointer;

	//refer-member, valid for class and union
	CCDK_FORCEINLINE  value_type operator->() const noexcept  { static_assert(or_v<is_class<T>, is_union<T>>, "T need class and union"); return pointer();  }

	//deref, type can't be void, assert not nullptr 
	CCDK_FORCEINLINE add_lref_t<T> operator*() const noexcept { ccdk_assert(pointer() != nullptr); return *pointer(); }
};


//for array implements
// no member operation
// no dereference operation
// has index operation
// only support same style share_ptr copy / move
template<
	typename T,
	typename Deleter,  
	typename RefCount 
>
class share_ptr<T[], Deleter, RefCount>: public share_ptr_base<T[],Deleter,RefCount>
{
public:
	typedef  share_ptr_base<T[], Deleter, RefCount> base_type;
	typedef typename base_type::value_type        value_type;

	//base constructor
	using base_type::base_type;
	using base_type::operator=;
	using base_type::swap;
	using base_type::share_count;
	using base_type::pointer;

	//index, valid only for array
	CCDK_FORCEINLINE add_lref_t<T> operator[](uint32 index) & noexcept { return pointer()[index]; }
	CCDK_FORCEINLINE add_const_lref_t<T> operator[](uint32 index) const& noexcept { return pointer()[index]; }
};

//forbidden void 
template< typename Deleter, typename RefCount > class share_ptr<void, Deleter, RefCount> {};


//help fn
template<typename T,typename D,typename R, typename T2, typename D2, typename R2>
CCDK_FORCEINLINE void swap(share_ptr<T, D, R>& lh, share_ptr<T2, D2, R2>& rh) noexcept { lh.swap(rh); }
template<typename T, typename D, typename R>
CCDK_FORCEINLINE decltype(auto) value(const share_ptr<T, D, R>& sp) { return sp.pointer(); }


// share_ptr == share_ptr / nullptr == share_ptr /  share_ptr == nullptr
template<typename T1, typename D1,  typename R1, typename T2, typename D2, typename R2>
CCDK_FORCEINLINE bool operator==(const share_ptr<T1, D1, R1>& lh, const share_ptr<T2, D2, R2>& rh) { return lh.pointer() == rh.pointer(); }
template<typename T1, typename D1, typename R1>
CCDK_FORCEINLINE bool operator==(const share_ptr<T1, D1, R1>& lh, ptr::nullptr_t) { return lh.pointer() == nullptr; }
template<typename T1, typename D1, typename R1>
CCDK_FORCEINLINE bool operator==(ptr::nullptr_t, const share_ptr<T1, D1, R1>& rh) { return rh.pointer() == nullptr; }

// share_ptr < share_ptr / share_ptr < nullptr_t /  share_ptr < nullptr_t
template<typename T1, typename D1, typename R1, typename T2, typename D2, typename R2>
CCDK_FORCEINLINE bool operator<(const share_ptr<T1, D1, R1>& lh, const share_ptr<T2, D2, R2>& rh) { return util::comp_less< typename share_ptr<T1, D1, R1>::value_type, typename share_ptr<T2, D2, R2>::value_type >(lh.pointer(), rh.pointer()); }
template<typename T1, typename D1, typename R1>
CCDK_FORCEINLINE bool operator<(ptr::nullptr_t, const share_ptr<T1, D1, R1>& rh) noexcept { return util::comp_less< ptr::nullptr_t, typename share_ptr<T1, D1, R1>::value_type>(nullptr, rh.pointer()); }
template<typename T1, typename D1, typename R1>
CCDK_FORCEINLINE bool operator<(const share_ptr<T1, D1, R1>& lh, ptr::nullptr_t) noexcept { return util::comp_less< ptr::nullptr_t, typename share_ptr<T1, D1, R1>::value_type>( lh.pointer(), nullptr ); }




ccdk_namespace_mpl_util_end