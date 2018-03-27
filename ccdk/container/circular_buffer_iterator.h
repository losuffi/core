#pragma once

#include<ccdk/container/container_mudule.h>
#include<ccdk/mpl/iterator/iterator_fwd.h>
#include<ccdk/mpl/util/move.h>

ccdk_namespace_ct_start

using namespace ccdk::mpl;

template<typename T, typename Size>
struct circular_buffer_iterator
{
	typedef circular_buffer_iterator	 this_type;
	typedef T							 value_type;
	typedef T*							 pointer_type;
	typedef T&							 reference_type;
	typedef T const&					 const_reference_type;
	typedef ptr::diff_t					 difference_type;
	typedef Size					     size_type;
	typedef random_category			     category;

	pointer_type base;
	size_type    cap;
	size_type    offset;

	
	/* ++it */
	CCDK_FORCEINLINE this_type& operator++() noexcept {
		offset = (offset + 1) % cap;
		return *this;
	}

	/* it++ */
	CCDK_FORCEINLINE this_type operator++(int) const noexcept {
		return { base, cap, (offset + 1) % cap };
	}

	/* it+step */
	CCDK_FORCEINLINE constexpr this_type operator+(size_type step) const noexcept {
		return { base, cap, (offset + step) % cap };
	}

	/* it+=step */
	CCDK_FORCEINLINE this_type& operator+=(size_type step) noexcept {
		offset = (offset + step) % cap;
		return *this;
	}

	/* deref */
	CCDK_FORCEINLINE reference_type operator*() noexcept {
		ccdk_assert(offset >= 0 && offset < cap);
		return base[offset];
	}

	CCDK_FORCEINLINE const_reference_type operator*() const noexcept { 
		ccdk_assert(offset >= 0 && offset < cap);
		return base[offset]; 
	}

	/* index */
	CCDK_FORCEINLINE reference_type operator[](size_type index) noexcept {
		ccdk_assert(offset + index >= 0 && offset + index < cap);
		return base[offset + index];
	}

	CCDK_FORCEINLINE const_reference_type operator[](size_type index) const noexcept {
		ccdk_assert( offset+index >= 0 && offset+index < cap);
		return base[offset+index];
	}

	/* cmp */
	CCDK_FORCEINLINE bool operator==(this_type const& other) const noexcept {
		return base == other.base && offset == other.offset && cap == other.cap;
	}

	/* cmp */
	CCDK_FORCEINLINE bool operator!=(this_type const& other) const noexcept {
		return base != other.base || offset != other.offset || cap != other.cap;
	}
};


template<typename T, typename Size>
struct reverse_circular_buffer_iterator
{
	typedef reverse_circular_buffer_iterator	 this_type;
	typedef T							 value_type;
	typedef T*							 pointer_type;
	typedef T&							 reference_type;
	typedef T const&					 const_reference_type;
	typedef ptr::diff_t					 difference_type;
	typedef Size					     size_type;
	typedef random_category			     category;

	pointer_type base;
	size_type    cap;
	size_type    offset;


	/* ++it */
	CCDK_FORCEINLINE this_type& operator++() noexcept {
		offset = (offset - 1 + cap) % cap;
		return *this;
	}

	/* it++ */
	CCDK_FORCEINLINE this_type operator++(int) const noexcept {
		return { base, cap, (offset - 1 + cap) % cap };
	}

	/* it+step */
	CCDK_FORCEINLINE constexpr this_type operator+(size_type step) const noexcept {
		ccdk_assert(step < cap);
		return { base, cap, (offset - step + cap) % cap };
	}

	/* deref */
	CCDK_FORCEINLINE reference_type operator*() noexcept {
		ccdk_assert(offset >= 0 && offset < cap);
		return base[offset];
	}

	CCDK_FORCEINLINE const_reference_type operator*() const noexcept {
		ccdk_assert(offset >= 0 && offset < cap);
		return base[offset];
	}

	/* index */
	CCDK_FORCEINLINE reference_type operator[](size_type index) noexcept {
		ccdk_assert(offset + index >= 0 && offset + index < cap);
		return base[offset + index];
	}

	CCDK_FORCEINLINE const_reference_type operator[](size_type index) const noexcept {
		ccdk_assert(offset + index >= 0 && offset + index < cap);
		return base[offset + index];
	}

	/* it+=step */
	CCDK_FORCEINLINE this_type& operator+=(size_type step) noexcept {
		offset = (offset + step) % cap;
		return *this;
	}

	/* cmp */
	CCDK_FORCEINLINE bool operator==(this_type const& other) const noexcept {
		return base == other.base && offset == other.offset && cap == other.cap;
	}

	/* cmp */
	CCDK_FORCEINLINE bool operator!=(this_type const& other) const noexcept {
		return base != other.base || offset != other.offset || cap != other.cap;
	}
};

ccdk_namespace_ct_end

