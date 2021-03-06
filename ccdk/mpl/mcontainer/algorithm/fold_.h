#pragma once

#include<ccdk/mpl/mpl_module.h>
#include<ccdk/mpl/base/type_.h>
#include<ccdk/mpl/base/apply_.h>
#include<ccdk/mpl/base/derive_if.h>
#include<ccdk/mpl/mcontainer/mcontainer_fwd.h>
#include<ccdk/mpl/mcontainer/iterator_.h>
#include<ccdk/mpl/mcontainer/algorithm/lambda_.h>

ccdk_namespace_mpl_start


namespace mpl_impl
{
	/* iter left fold, (((((Prev,1),2),3),4),5) */
	template<typename Begin, typename End, typename Prev, typename Binary>
	struct iter_fold_left_impl :
				iter_fold_left_impl< 
					next_t<Begin>, End, 
					apply_t<Binary, Prev, deref_t<Begin>>, Binary> {};

	template<typename End, typename Prev, typename Binary>
	struct iter_fold_left_impl<End, End, Prev, Binary> { typedef Prev type; };

	/* reverse iter left fold, (Prev, ( 1, ( 2, (3, (4,5))))) */
	template<typename Begin, typename End, typename Prev, typename Binary>
	struct iter_fold_right_impl
	{
		typedef apply_t<Binary, Prev,
			typename iter_fold_right_impl<  next_t<Begin>, End, deref_t<Begin>, Binary>::type
		> type;
	};

	template<typename End, typename Prev, typename Binary>
	struct iter_fold_right_impl<End, End, Prev, Binary> { typedef Prev type; };

	/* iter right fold, (5,(4,(3,(2,(1,Prev))))) */
	template<typename Begin, typename End, typename Prev, typename Binary>
	struct iter_reverse_fold_right_impl :
		iter_reverse_fold_right_impl< next_t<Begin>, End, apply_t< Binary, deref_t<Begin>, Prev>, Binary> {};

	template<typename End, typename Prev, typename Binary>
	struct iter_reverse_fold_right_impl<End, End, Prev, Binary> { typedef Prev type; };

	/* reverse iter left fold (((((Prev,5),4),3),2),1) */
	template<typename Begin, typename End, typename Prev, typename Binary>
	struct iter_reverse_fold_left_impl
	{
		typedef apply_t< Binary, 
			typename iter_reverse_fold_left_impl<  next_t<Begin>, End, Prev, Binary>::type,
			deref_t<Begin>
		> type;
	};

	template<typename End, typename Prev, typename Binary>
	struct iter_reverse_fold_left_impl<End, End, Prev, Binary> { typedef Prev type; };

}

/* iter_fold */
template<typename Begin, typename End, typename Prev, typename Binary>
struct iter_fold_left_ :mpl_impl::iter_fold_left_impl<Begin, End, Prev, lambda_<Binary>> {};

template<typename Begin, typename End, typename Prev, typename Binary>
struct iter_fold_right_ :mpl_impl::iter_fold_right_impl<Begin, End, Prev, lambda_<Binary>> {};

template<typename Begin, typename End, typename Prev, typename Binary>
struct iter_reverse_fold_right_ :mpl_impl::iter_reverse_fold_right_impl<Begin, End, Prev, lambda_<Binary>> {};

template<typename Begin, typename End, typename Prev, typename Binary>
struct iter_reverse_fold_left_ :mpl_impl::iter_reverse_fold_left_impl<Begin, End, Prev, lambda_<Binary>> {};

/* fold */
template<typename Container, typename Prev, typename Binary>
struct fold_left_ : iter_fold_left_< begin_t<Container>, end_t<Container>, Prev, Binary> {};

template<typename Container, typename Prev, typename Binary>
struct fold_right_ : iter_fold_right_< begin_t<Container>, end_t<Container>, Prev, Binary> {};

template<typename Container, typename Prev, typename Binary>
struct reverse_fold_left_ : iter_reverse_fold_left_< begin_t<Container>, end_t<Container>, Prev, Binary> {};

template<typename Container, typename Prev, typename Binary>
struct reverse_fold_right_ : iter_reverse_fold_right_< begin_t<Container>, end_t<Container>, Prev, Binary> {};

/* fold alias */
template<typename Container, typename Prev, typename Binary>
using fold_left_t = typename fold_left_<Container, Prev, Binary>::type;

template<typename Container, typename Prev, typename Binary>
using fold_right_t = typename fold_right_<Container, Prev, Binary>::type;

template<typename Container, typename Prev, typename Binary>
using reverse_fold_left_t = typename reverse_fold_left_<Container, Prev, Binary>::type;

template<typename Container, typename Prev, typename Binary>
using reverse_fold_right_t = typename reverse_fold_right_<Container, Prev, Binary>::type;

/* iter fold alias */
template<typename Begin, typename End, typename Prev, typename Binary>
using iter_fold_left_t = typename iter_fold_left_<Begin,End, Prev, Binary>::type;

template<typename Begin, typename End, typename Prev, typename Binary>
using iter_fold_right_t = typename iter_fold_right_<Begin, End, Prev, Binary>::type;

template<typename Begin, typename End, typename Prev, typename Binary>
using iter_reverse_fold_left_t = typename iter_reverse_fold_left_<Begin, End, Prev, Binary>::type;

template<typename Begin, typename End, typename Prev, typename Binary>
using iter_reverse_fold_right_t = typename iter_reverse_fold_right_<Begin, End, Prev, Binary>::type;

ccdk_namespace_mpl_end