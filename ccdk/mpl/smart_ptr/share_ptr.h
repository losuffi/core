#pragma once

#include<ccdk/mpl/mpl_module.h>
#include<ccdk/mpl/type_traits/is_convertible.h>
#include<ccdk/mpl/base/enable_if.h>
#include<ccdk/mpl/util/noncopyable.h>
#include<ccdk/mpl/util/swap.h>
#include<ccdk/mpl/smart_ptr/normal_deleter.h>

ccdk_namespace_mpl_sp_start

//non-thread safe ref_count
class default_ref_count
{
private:
	//resource memory only shared between share_ptr, last share_ptr release will delete resource memory
	uint32 shared_count;
	//this will be shared between share_ptr and weak_ptr, unless last share_ptr or weak_ptr is release, this will not release
	uint32 ref_count;
public:

	CCDK_FORCEINLINE
	default_ref_count() noexcept
		:shared_count{ 0 }, ref_count{ 0 }
	{}

	CCDK_FORCEINLINE
	default_ref_count(uint32 inShareCount, uint32 inRefCount) noexcept
		:shared_count{inShareCount},
			ref_count{inRefCount}
	{}

	template<typename Deleter, typename Class>
	CCDK_FORCEINLINE
	void dec_share_count(const Deleter& del, Class*& ptr)
	{
		if (--shared_count == 0)
		{
			del(ptr);
		}
	}

	CCDK_FORCEINLINE
	void inc_share_count()
	{
		++shared_count;
	}

	CCDK_FORCEINLINE
	void decrease_ref_count()
	{
		if (--ref_count == 0)
		{
			//destroy RefCount
			delete this; 
		}
	}

	CCDK_FORCEINLINE
		void increase_ref_count()
	{
		++ref_count;
	}
};

//for non-void / non-array / non-thread-safe implements
template<
	typename Class,
	typename Deleter = normal_deleter,     //array need normal_array_deleter
	typename RefCount = default_ref_count  //multi-thread need atomic ref_count, need nothrow constructor
>
class share_ptr
{
	typedef Class* value_type;
private:
	RefCount* ref_count;
	Class*    content;
public:

	//default constructor
	CCDK_FORCEINLINE
		share_ptr() noexcept
		:ref_count{ nullptr }, content{ nullptr }
	{}

	//nullptr constructor
	CCDK_FORCEINLINE
		share_ptr(ptr::nullptr_t) noexcept
		: ref_count{ nullptr }, 
			content{ nullptr }
	{}

	//ptr constructor
	//derived class can also transfered use ptr
	//RefCount need a noexcept constructor
	CCDK_FORCEINLINE explicit
		share_ptr(value_type ptr) noexcept
		: ref_count{ new RefCount{1,1} },
			content{ ptr }
	{}

	//copy constructor
	//Class1 must be base of Class2
	template<
		typename Class2,
		typename = check_t< is_convertible<Class*,Class2*> >
	>
	CCDK_FORCEINLINE
	share_ptr(const share_ptr<Class2> & other) noexcept
		: ref_count{ other.ref_count },
			content{ other.content }
	{
		ref_count->inc_share_count();
	}

	//move constructor
	template<
		typename Class2,
		typename = check_t< is_convertible<Class*, Class2*> >
	>
	CCDK_FORCEINLINE
	share_ptr(share_ptr<Class2>&& other) noexcept
	{
		other.swap(*this);          //move to this
		share_ptr{}.swap(other);    //release other
	}

	//assign
	CCDK_FORCEINLINE
	share_ptr& operator=(value_type ptr)
	{
		share_ptr{ ptr }.swap(*this);
		return *this;
	}

	//copy assign
	template<
		typename Class2,
		typename = check_t< is_convertible<Class*, Class2*> >
	>
	CCDK_FORCEINLINE
	share_ptr& operator=(const share_ptr<Class2>& other)
	{
		share_ptr{ other }.swap(*this);
		return *this;
	}

	//copy assign
	template<
		typename Class2,
		typename = check_t< is_convertible<Class*, Class2*> >
	>
		CCDK_FORCEINLINE
		share_ptr& operator=(share_ptr<Class2>&& other)
	{
		other.swap(*this);
		share_ptr{}.swap(other);
		return *this;
	}

	//swap operation
	template<
		typename Class2,
		typename = check_t< is_convertible<Class*, Class2*> >
	>
	CCDK_FORCEINLINE
	void swap(share_ptr<Class2>& other) noexcept
	{
		util::swap(ref_count, other.ref_count);
		util::swap(content, other.content);
	}

	CCDK_FORCEINLINE
		~share_ptr()
	{
		//not store Deleter
		ref_count->decrease_share_count(Deleter{}, content);
	}
};

//for non-void / non-array / non-thread-safe implements
template<
	typename Class,
	typename Deleter = normal_array_deleter, //array delete
	typename RefCount = default_ref_count    //multi-thread need atomic ref_count, need nothrow constructor
>
class share_ptr<Class[]>
{

};





ccdk_namespace_mpl_sp_end