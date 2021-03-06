#pragma once

#include<ccdk/container/container_mudule.h>
#include<ccdk/mpl/base/compile_check.h>
#include<ccdk/container/slist.h>

ccdk_namespace_ct_start

using namespace ccdk::mpl;

template<
	typename T,
	typename Size = uint32,
	typename Alloc = mem::simple_new_allocator<T, Size>,
	typename Base = slist<T,Size,Alloc>
>
class queue
{
public:
	using base_type = Base;
	using this_type = queue;
	using value_type = T;
	using pointer  = T * ;
	using const_pointer = T const*;
	using reference = T & ;
	using const_reference = T const&;
	using size_type = Size;
	using difference_type = to_signed_t<size_type>;
private:
	Base  content;
public:

	//empty ctor
	CCDK_FORCEINLINE queue() :content{} {}

	//copy ctor
	CCDK_FORCEINLINE queue(this_type const& other) : content{ other.content } {}

	//move ctor
	CCDK_FORCEINLINE queue(this_type&& other) : content{ util::move(other.content) } {}

	//base container copy ctor
	CCDK_FORCEINLINE queue(Base const& base) : content{ base } {}

	//base container move ctor
	CCDK_FORCEINLINE queue(Base && base) : content{ util::move(base) } {}

	//array ctor
	template<uint32 N>
	CCDK_FORCEINLINE queue(T const(&arr)[N]) : content{ arr } {}

	//swap
	CCDK_FORCEINLINE void swap(this_type& other) {
		util::swap(content, other.content);
	}

	//assign copy
	CCDK_FORCEINLINE this_type& operator=(this_type const& other) {
		content = other.content;
		return *this; 
	}

	//assign move
	CCDK_FORCEINLINE this_type& operator=(this_type && other) {
		content = util::move(other.content);
		return *this;
	}

	//push / pop
	CCDK_FORCEINLINE void pop() { content.pop_front(); }
	CCDK_FORCEINLINE void push(T const& t) { content.push_back(t); }
	CCDK_FORCEINLINE void push(T && t) { content.push_back(util::move(t)); }
	template<typename... Args>
	CCDK_FORCEINLINE void emplace(Args &&... args) { content.emplace_back(util::forward<Args>(args)...); }

	//front / back
	CCDK_FORCEINLINE reference front() noexcept { return content.front(); }
	CCDK_FORCEINLINE const_reference front() const noexcept { return content.front(); }
	CCDK_FORCEINLINE reference back() noexcept { return content.back(); }
	CCDK_FORCEINLINE const_reference back() const noexcept { return content.back(); }

	//size / empty
	CCDK_FORCEINLINE size_type size() const noexcept { return content.size(); }
	CCDK_FORCEINLINE size_type empty() const noexcept { return content.empty(); }
};


template<
	typename T,
	uint32 CacheSize = 10,
	typename Size = uint32,
	typename Alloc = mem::simple_new_allocator<T, Size>
>
using cached_queue = queue<T, Size, Alloc, cached_slist<T, CacheSize, Size, Alloc>>;


ccdk_namespace_ct_end