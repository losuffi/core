#pragma once

#include<ccdk/container/container_mudule.h>
#include<ccdk/mpl/base/compile_check.h>
#include<ccdk/mpl/base/logic_.h>
#include<ccdk/mpl/base/compatible_op.h>
#include<ccdk/mpl/type_traits/is_same.h>
#include<ccdk/mpl/iterator/iterator_traits.h>
#include<ccdk/mpl/iterator/bit_iterator.h>
#include<ccdk/mpl/iterator/reverse_iterator.h>
#include<ccdk/mpl/iterator/algorithm/distance.h>
#include<ccdk/mpl/util/copy.h>
#include<ccdk/mpl/util/swap.h>
#include<ccdk/memory/allocator/simple_new_allocator.h>
#include<ccdk/memory/allocator_traits.h>

ccdk_namespace_ct_start

using namespace ccdk::mpl;

/* fit bytes with a inner basic type  */
#define RECURSIVE_TYPEDEF(Type) using type =  typename fit_bytes<Bytes,Type, Bytes <=sizeof(Type)>::type
template<uint32 Bytes, typename T = uint8 , bool Fit = (Bytes<= sizeof(T)) > struct fit_bytes;
template<uint32 Bytes, typename T> struct fit_bytes<Bytes, T, true> { typedef T type[ (Bytes+ sizeof(T)-1) / sizeof(T)];  };
template<uint32 Bytes> struct fit_bytes<Bytes, uint8, false>  { RECURSIVE_TYPEDEF(uint16); };
template<uint32 Bytes> struct fit_bytes<Bytes, uint16, false> { RECURSIVE_TYPEDEF(uint32); };
template<uint32 Bytes> struct fit_bytes<Bytes, uint32, false> { RECURSIVE_TYPEDEF(uint64); };
template<uint32 Bytes> struct fit_bytes<Bytes, uint64, false>:fit_bytes<Bytes, uint32, true> {  };
#undef RECURSIVE_TYPEDEF

template<typename T, typename Char>
constexpr T parse_int(const Char* str, uint32 pos, uint32 max) {
	uint32 begin = pos * 16;
	if (begin >= max) return 0;
	uint32 end =  begin + 16;
	end = max < end ? max : end;
	T val = 0;
	for (uint32 i = begin; i < end; ++i) {
		val = cbitor<T>( val << T(1), str[i] - '0');
	}
	return val;
}

template< uint64 NBit >
class fix_bitset 
{
public:
	/* common */
	static constexpr uint64 Bytes = (NBit + 7) / 8;
	using this_type   = fix_bitset;
	using array_type  = typename fit_bytes<Bytes>::type;
	using single_type = remove_dim_t<array_type>;
	static constexpr uint64 N                  = sizeof(array_type) / sizeof(single_type);
	static constexpr single_type kOne          = 1;
	static constexpr single_type kStoreBits    = sizeof(single_type) * 8;
	static constexpr single_type kTopMask      = kOne << (kStoreBits - 1);
	static constexpr single_type kLastOffset   = NBit / kStoreBits;
	static constexpr single_type kLastMask     = kOne << (NBit % kStoreBits);
	static constexpr single_type kReverseOffst = (NBit - 1) / kStoreBits;
	static constexpr single_type kReverseMask  = kOne <<((NBit - 1) % kStoreBits);

	/* container */
	using value_type      = single_type;
	using pointer         = value_type*;
	using const_pointer   = value_type const*;
	using reference       = it::bit_access<value_type>;
	using const_reference = bool;
	using size_type       = uint32;
	using difference_type = ptr::diff_t;
	

	/* typedef iterator */
	using iterator               = it::iterator<bit_random_category, value_type, size_type>;
	using const_iterator         = it::iterator<bit_random_category, const value_type, size_type>;
	using reverse_iterator       = it::reverse_iterator<iterator>;
	using const_reverse_iterator = it::reverse_iterator<const_iterator>;

	/* friend */
	template<uint64 NBit2> friend class fix_bitset;

private:
	value_type content[N];

	/* aux compile-time fill-ctor */
	template<value_type... Args>
	CCDK_FORCEINLINE constexpr fix_bitset(mpl::val_pack<value_type, Args...>) 
		noexcept : content{ Args... } {}

	/* aux compile-time fill from constexpr-string */
	template<typename Char, value_type... Args>
	CCDK_FORCEINLINE constexpr fix_bitset(const Char* str, uint32 L,
		mpl::val_pack<uint32, Args...>)
		noexcept : content{ parse_int<value_type,Char>(str, Args, L)... } { }

	/* aux compile-time copy */
	template<value_type... Args>
	CCDK_FORCEINLINE constexpr fix_bitset(const value_type* other, mpl::val_pack<uint32, Args...>)
		noexcept : content{ other[Args]... } {
	}

public:
	/* constexpr default */
	CCDK_FORCEINLINE constexpr fix_bitset() noexcept : content{ 0 } {}
	CCDK_FORCEINLINE constexpr fix_bitset(ptr::nullptr_t) noexcept : content{ 0 } {}

	/* compile time fill */
	template<bool v>
	CCDK_FORCEINLINE constexpr fix_bitset(mpl::bool_<v>) noexcept
		:fix_bitset(mpl::dup_to_val_pack_c<N,value_type,v?-1:0>) {}

	/* compile time fill from constexpr string, exclude end '\0' */
	template<typename Char, ptr::size_t L>
	CCDK_FORCEINLINE constexpr explicit fix_bitset(
		from_string_literial, Char(&str)[L]) noexcept
		: fix_bitset(str, mpl::min_val<uint32, NBit,L-1>, mpl::make_indice_c<N> ){}

	/* runtime fill */
	CCDK_FORCEINLINE explicit fix_bitset(bool v) noexcept {
		memset(content, v ? 0b11111111 : 0b00000000, Bytes);
	} 

	/* runtime string */
	CCDK_FORCEINLINE explicit fix_bitset(char const* str) noexcept :content{ 0 } {
		ptr::size_t len = (ptr::size_t)fn::min(NBit, strlen(str));
		for (uint32 i = 0; i < N; ++i) {
			for (uint32 j = 0; j < kStoreBits; ++j) {
				uint32 pos = shl_bits<kStoreBits,uint32>(i) + j;
				if (pos >= len) return;
				ccdk_assert(str[pos] - '0' == 1 || str[pos] - '0' == 0);
				content[i] |= cshl<value_type>( (str[pos] - '0'),  j);
			}
		}
	}

	/* range-n copy */
	template<typename InputIt, typename = check_t< is_iterator<InputIt>> >
	CCDK_FORCEINLINE fix_bitset(InputIt beginIt, size_type n) noexcept:content { 0 } {
		util::copy_n(begin(), beginIt, fn::min(NBit, n) );
	}

	/* range copy */
	template<typename InputIt, typename = check_t< is_iterator<InputIt>> >
	CCDK_FORCEINLINE fix_bitset(InputIt beginIt, InputIt endIt) noexcept {
		util::copy_n(begin(), beginIt, fn::min(NBit, it::distance(beginIt, endIt)));
	}

	/* compile copy */
	CCDK_FORCEINLINE constexpr fix_bitset(fix_bitset const& other)
		noexcept:fix_bitset{ other.content, mpl::make_indice_c<N> } { }

	/* template copy */
	template<uint32 NBit2>
	CCDK_FORCEINLINE fix_bitset(fix_bitset<NBit2> const& other) noexcept : content{} {
		memcpy(content, other.content, (ptr::size_t)fn::min(Bytes, other.Bytes));
	}

	/* swap */
	CCDK_FORCEINLINE void swap(fix_bitset& other) {
		util::swap(content, other.content);
	}

/////////////////////////////////////////////////////////////////////////////////
//// assign operation 

	/* copy assign */
	CCDK_FORCEINLINE this_type& operator=(fix_bitset const& other) {
		for (uint32 i = 0; i < N; ++i) { content[i] = other.content[i]; }
		return *this;
	}

	/* template copy assign */
	template<uint32 NBit2>
	CCDK_FORCEINLINE this_type& operator=(fix_bitset<NBit2> const& other) {
		memcpy(content, other.content, (ptr::size_t)fn::min(Bytes, other.Bytes));
		return *this;
	}

	/* fill assign */
	CCDK_FORCEINLINE this_type& operator=(bool v) {
		memset(content, v ? 0b11111111 : 0b00000000, Bytes);
		return *this;
	}

	/* fill range */
	CCDK_FORCEINLINE this_type& assign(size_type start, size_type end, bool v) {
		ccdk_assert(start < end && end <= NBit);
		for (size_type i = start; i < end; ++i) at(i) = v;
		return *this;
	}

	template<typename InputIt, typename = check_t< is_iterator<InputIt>> >
	CCDK_FORCEINLINE this_type& assign(InputIt beginIt, ptr::size_t n) {
		ccdk_assert(n <= NBit);
		util::copy_n(begin(), beginIt, n);
	}

	template<typename InputIt, typename = check_t< is_iterator<InputIt>> >
	CCDK_FORCEINLINE this_type& assign(InputIt beginIt, InputIt endIt) {
		util::copy_range(begin(), beginIt, endIt);
	}

/////////////////////////////////////////////////////////////////////////////////
//// iterator

	CCDK_FORCEINLINE iterator begin() noexcept { return { content, 0, 1, N}; }
	CCDK_FORCEINLINE iterator end() noexcept { return { content, kLastOffset, kLastMask , N }; }
	CCDK_FORCEINLINE const_iterator begin() const noexcept { return { content, 0, 1, N }; }
	CCDK_FORCEINLINE const_iterator end() const noexcept { return { content, kLastOffset, kLastMask , N }; }
	CCDK_FORCEINLINE constexpr const_iterator cbegin() const noexcept { return { content, 0, 1, N }; }
	CCDK_FORCEINLINE constexpr const_iterator cend() const noexcept { return { content, kLastOffset, kLastMask , N }; }
	CCDK_FORCEINLINE reverse_iterator rbegin() noexcept { return { { content, kReverseOffst, kReverseMask , N } }; }
	CCDK_FORCEINLINE reverse_iterator rend() noexcept { return { {content, size_type(-1),kTopMask, N } }; }
	CCDK_FORCEINLINE const_reverse_iterator rbegin() const noexcept { return { { content, kReverseOffst, kReverseMask , N } }; }
	CCDK_FORCEINLINE const_reverse_iterator rend() const noexcept { return { { content, size_type(-1),kTopMask, N } }; }
	CCDK_FORCEINLINE constexpr const_reverse_iterator crbegin() const noexcept { return { { content, kReverseOffst, kReverseMask, N } }; }
	CCDK_FORCEINLINE constexpr const_reverse_iterator crend() const noexcept { return { { content, size_type(-1), kTopMask, N } }; }

/////////////////////////////////////////////////////////////////////////////////
//// readonly attribute

	CCDK_FORCEINLINE constexpr size_type size() { return NBit; }
	CCDK_FORCEINLINE constexpr size_type capcity() { return Bytes * 8; }
	CCDK_FORCEINLINE constexpr size_type max_size() { return size_type(-1) / sizeof(value_type); }

////////////////////////////////////////////////////////////////////////////////
//// element operation

	/* index */
	CCDK_FORCEINLINE reference operator[](size_type index) noexcept {
		ccdk_assert(index < NBit);
		return { content[index / kStoreBits], cshl<value_type>(1, index % kStoreBits) };
	}

	/* const index, return bool */
	CCDK_FORCEINLINE constexpr const_reference operator[](size_type index) const noexcept {
		ccdk_assert(index < NBit);
		return content[index / kStoreBits] & cshl<value_type>(1, index % kStoreBits);
	}
	CCDK_FORCEINLINE reference at(size_type index) noexcept {
		ccdk_assert(index < NBit );
		return { content[index / kStoreBits], cshl<value_type>(1,index%kStoreBits) };
	}
	CCDK_FORCEINLINE constexpr const_reference at(size_type index) const noexcept {
		//ccdk_assert(index < NBit);
		return content[index / kStoreBits] & cshl<value_type>(1,(index % kStoreBits));
	}

	/* last bit reference */
	CCDK_FORCEINLINE reference back()  noexcept {
		return { content[len / kStoreBits], cshl<value_type>(1, index % kStoreBits) };
	}

	/* last bit value */
	CCDK_FORCEINLINE constexpr const_reference back() const noexcept {
		return { content[len / kStoreBits], cshl<value_type>(1, NBit % kStoreBits) };
	}


//////////////////////////////////////////////////////////////////////////////////
//// bit operation

	CCDK_FORCEINLINE constexpr size_type count_one() {
		auto e = end();
		auto count = 0;
		for (auto it = begin(); it != e; ++it)
			if (*it) ++count;
		return count;
	}

	CCDK_FORCEINLINE constexpr size_type count_zero() {
		return NBit - count_one();
	}

	/* weather all bit is set */
	CCDK_FORCEINLINE constexpr bool all() {
		for (int i = 0; i < N; ++i) {
			if (content[i] != value_type(-1)) return false;
		}
		return true;
	}

	/* weather at least 1bit is set */
	CCDK_FORCEINLINE constexpr bool any() {
		for (int i = 0; i < N; ++i) {
			if (content[i] != 0) return true;
		}
		return false;
	}

	/* none bit is set */
	CCDK_FORCEINLINE constexpr bool none() { return !any(); }

	/* operation */
	CCDK_FORCEINLINE this_type& operator&=(this_type const& other) noexcept {
		for (int i = 0; i < N; ++i) { content[i] &= other.content[i]; }
		return *this;
	}
	CCDK_FORCEINLINE this_type& operator|=(this_type const& other) noexcept {
		for (int i = 0; i < N; ++i) { content[i] |= other.content[i]; }
		return *this;
	}
	CCDK_FORCEINLINE this_type& operator^=(this_type const& other) noexcept {
		for (int i = 0; i < N; ++i) { content[i] ^= other.content[i]; }
		return *this;
	}
	CCDK_FORCEINLINE this_type& flip() noexcept {
		for (int i = 0; i < N; ++i) { content[i] = ~content[i]; }
		return *this;
	}
	/* not circler shift right */
	CCDK_FORCEINLINE this_type& operator<<=(size_type shl) noexcept {
		if (shl > 0) {
			int32 wsft = shl / kStoreBits;
			int32 wsft1 = wsft + 1;
			int32 lsft = shl - wsft*kStoreBits;
			int32 hsft = kStoreBits - lsft;
			if (N > wsft1) {
				for (int32 i = 0; i < N - wsft1; ++i) {
					content[i] = (content[i + wsft] >> lsft) | (content[i + wsft1] << hsft);
				}
			}
			content[N- wsft1] = content[N-1] >> lsft;
			memset(content+N-wsft, 0, wsft*Bytes);
		}
		return *this;
	}

	CCDK_FORCEINLINE this_type& operator>>=(size_type shr) noexcept {
		if (shr > 0) {
			int32 wsft = shr / kStoreBits;
			int32 wsft1 = wsft + 1;
			int32 lsft = shr - wsft * kStoreBits;
			int32 hsft = kStoreBits - lsft;
			if (N > wsft) {
				for (int32 i = N - 1; i > wsft; --i) {
					content[i] = (content[i - wsft] << lsft) | (content[i - wsft1] >> hsft);
				}
			}
			
			content[wsft] = content[0] << lsft;
			memset(content , 0, wsft*sizeof(value_type));
		}
		return *this;
	}

	CCDK_FORCEINLINE this_type operator&(this_type const& other) const noexcept {
		return this_type{ *this } &= other;
	}
	CCDK_FORCEINLINE this_type operator|(this_type const& other) const noexcept {
		return this_type{ *this } |= other;
	}
	CCDK_FORCEINLINE this_type operator^(this_type const& other) const noexcept {
		return this_type{ *this } ^= other;
	}
	CCDK_FORCEINLINE this_type operator>>(size_type pos) const noexcept {
		return this_type{ *this } >>= pos;
	}
	CCDK_FORCEINLINE this_type operator<<(size_type pos) const noexcept {
		return this_type{ *this } <<= pos;
	}
	CCDK_FORCEINLINE this_type operator~() noexcept {
		return this_type{ *this }.flip();
	}


///////////////////////////////////////////////////////////////////////////////
//// debug function 

	CCDK_FORCEINLINE void debug() const noexcept {
		char info[NBit + 1]{ 0 };
		for (int i = 0; i < NBit; ++i) {
			info[i] = this->at(i) ? '1' : '0';
		}
		DebugValue("fix_bit:", info);
	}

	CCDK_FORCEINLINE void debug_all() const noexcept {
		constexpr size_type len = shr_type<value_type, size_type>(NBit + kStoreBits);
		constexpr size_type len2 = shl_type<value_type, size_type>(len);
		char info[len2+1]{ 0 };
		for (int i = 0; i < len2; ++i) {
			info[i] = this->at(i) ? '1' : '0';
		}
		DebugValue("fix_bit:", info);
	}

	CCDK_FORCEINLINE constexpr bool operator==(this_type const& other) const noexcept {
		for (int i = 0; i < N; ++i) {
			if (content[i] != other.content[i]) return false;
		}
		return true;
	}


	CCDK_FORCEINLINE void debug_iterator() noexcept{
		char info[N*kStoreBits+1]{ 0 };
		int j = 0;
		
		for (auto i = begin(); i != end(); ++i,++j) {
			bool v = *i;
			info[j] = v ? '1' : '0';
		}
		DebugValue("fix_bit:", info);
	}

	CCDK_FORCEINLINE void debug_reverse_iterator() noexcept {
		char info[N*kStoreBits + 1]{ 0 };
		int j = 0;

		for (auto i = rbegin(); i != rend(); ++i, ++j) {
			bool v = *i;
			info[j] = v ? '1' : '0';
		}
		DebugValue("fix_bit reverse :", info);
	}

	CCDK_FORCEINLINE void debug_const_reverse_iterator() const noexcept {
		char info[N*kStoreBits + 1]{ 0 };
		int j = 0;

		for (auto i = crbegin(); i != crend(); ++i, ++j) {
			bool v = *i;
			info[j] = v ? '1' : '0';
		}
		DebugValue("fix_bit reverse :", info);
	}

	CCDK_FORCEINLINE void debug_const_iterator()  const noexcept {
		char info[N*kStoreBits + 1]{ 0 };
		int j = 0;

		for (auto i = cbegin(); i != cend(); ++i, ++j) {
		
			bool v = *i;
			info[j] = v ? '1' : '0';
		}
		DebugValue("fix_bit:", info);
	}
};

ccdk_namespace_ct_end