In file included from test_mpl_function.cpp:20:0:
../ccdk/mpl/function/combine.h: In instantiation of ‘constexpr ccdk::mpl::fn::combine_t<Fn, Fs>::combine_t(Fn&&, Fs&& ...) [with Fn = int (&)(const ccdk::test_copy_t&, int, const char*); Fs = {int (&)(int), int (&)(int)}]’:
../ccdk/mpl/util/create.h:18:53:   required from ‘constexpr auto ccdk::mpl::util::create_t<T>::operator()(Args&& ...) const [with Args = {int (&)(const ccdk::test_copy_t&, int, const char*), int (&)(int), int (&)(int)}; T = ccdk::mpl::fn::combine_t]’
test_mpl_function.cpp:372:40:   required from here
../ccdk/mpl/function/combine.h:22:126: error: no matching function for call to ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u, 2u>, int (&)(const ccdk::test_copy_t&, int, const char*), int (&)(int), int (&)(int)>::imap(<brace-enclosed initializer list>)’
   CCDK_FORCEINLINE constexpr combine_t(Fn && fn, Fs && ... fs) : content{  util::forward<Fn>(fn),  util::forward<Fs>(fs)...  } {}
                                                                                                                              ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:56:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> && other) : ipair < Indice, Args >{ util::move(other.template at<Indice>()) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:56:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:20:0:
../ccdk/mpl/function/combine.h:22:126: note:   mismatched types ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u, 2u>, Args2 ...>’ and ‘int(const ccdk::test_copy_t&, int, const char*)’
   CCDK_FORCEINLINE constexpr combine_t(Fn && fn, Fs && ... fs) : content{  util::forward<Fn>(fn),  util::forward<Fs>(fs)...  } {}
                                                                                                                              ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:52:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> const& other) : ipair < Indice, Args >{ other.template at<Indice>() }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:52:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:20:0:
../ccdk/mpl/function/combine.h:22:126: note:   mismatched types ‘const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u, 2u>, Args2 ...>’ and ‘int(const ccdk::test_copy_t&, int, const char*)’
   CCDK_FORCEINLINE constexpr combine_t(Fn && fn, Fs && ... fs) : content{  util::forward<Fn>(fn),  util::forward<Fs>(fs)...  } {}
                                                                                                                              ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:48:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&&) [with unsigned int ...Indice = {0u, 1u, 2u}; Args = {int (&)(const ccdk::test_copy_t&, int, const char*), int (&)(int), int (&)(int)}]
  CCDK_FORCEINLINE constexpr imap(imap && other) : ipair < Indice, Args >{ util::move(other) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:48:29: note:   candidate expects 1 argument, 3 provided
../ccdk/mpl/fusion/imap.h:45:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&) [with unsigned int ...Indice = {0u, 1u, 2u}; Args = {int (&)(const ccdk::test_copy_t&, int, const char*), int (&)(int), int (&)(int)}]
  CCDK_FORCEINLINE constexpr imap(imap const& other) : ipair < Indice, Args >{ other }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:45:29: note:   candidate expects 1 argument, 3 provided
../ccdk/mpl/fusion/imap.h:42:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(Args2&& ...)
  CCDK_FORCEINLINE constexpr imap(Args2 &&... args) : ipair<Indice, Args>{ util::forward<Args2>(args) }... {  }
                             ^~~~
../ccdk/mpl/fusion/imap.h:42:29: note:   template argument deduction/substitution failed:
../ccdk/mpl/fusion/imap.h:38:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap() [with unsigned int ...Indice = {0u, 1u, 2u}; Args = {int (&)(const ccdk::test_copy_t&, int, const char*), int (&)(int), int (&)(int)}]
  CCDK_FORCEINLINE constexpr imap() : ipair < Indice, Args >{}... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:38:29: note:   candidate expects 0 arguments, 3 provided
In file included from test_mpl_function.cpp:21:0:
../ccdk/mpl/function/dispatch.h: In instantiation of ‘constexpr ccdk::mpl::fn::dispatch_t<Fn, Fs>::dispatch_t(Fn&&, Fs&& ...) [with Fn = const ccdk::mpl::fn::add_t&; Fs = {const ccdk::mpl::fn::dec_t&, const ccdk::mpl::fn::inc_t&}]’:
../ccdk/mpl/util/create.h:18:53:   required from ‘constexpr auto ccdk::mpl::util::create_t<T>::operator()(Args&& ...) const [with Args = {const ccdk::mpl::fn::add_t&, const ccdk::mpl::fn::dec_t&, const ccdk::mpl::fn::inc_t&}; T = ccdk::mpl::fn::dispatch_t]’
test_mpl_function.cpp:379:35:   required from here
../ccdk/mpl/function/dispatch.h:23:132: error: no matching function for call to ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u>, const ccdk::mpl::fn::dec_t&, const ccdk::mpl::fn::inc_t&>::imap(<brace-enclosed initializer list>)’
   CCDK_FORCEINLINE constexpr  dispatch_t( Fn&& inFn, Fs&&... inFs) : fn{ util::forward<Fn>(inFn) }, fs{ util::forward<Fs>(inFs)... } {}
                                                                                                                                    ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:56:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> && other) : ipair < Indice, Args >{ util::move(other.template at<Indice>()) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:56:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:21:0:
../ccdk/mpl/function/dispatch.h:23:132: note:   types ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u>, Args2 ...>’ and ‘const ccdk::mpl::fn::dec_t’ have incompatible cv-qualifiers
   CCDK_FORCEINLINE constexpr  dispatch_t( Fn&& inFn, Fs&&... inFs) : fn{ util::forward<Fn>(inFn) }, fs{ util::forward<Fs>(inFs)... } {}
                                                                                                                                    ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:52:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> const& other) : ipair < Indice, Args >{ other.template at<Indice>() }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:52:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:21:0:
../ccdk/mpl/function/dispatch.h:23:132: note:   ‘const ccdk::mpl::fn::dec_t’ is not derived from ‘const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u>, Args2 ...>’
   CCDK_FORCEINLINE constexpr  dispatch_t( Fn&& inFn, Fs&&... inFs) : fn{ util::forward<Fn>(inFn) }, fs{ util::forward<Fs>(inFs)... } {}
                                                                                                                                    ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:48:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&&) [with unsigned int ...Indice = {0u, 1u}; Args = {const ccdk::mpl::fn::dec_t&, const ccdk::mpl::fn::inc_t&}]
  CCDK_FORCEINLINE constexpr imap(imap && other) : ipair < Indice, Args >{ util::move(other) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:48:29: note:   candidate expects 1 argument, 2 provided
../ccdk/mpl/fusion/imap.h:45:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&) [with unsigned int ...Indice = {0u, 1u}; Args = {const ccdk::mpl::fn::dec_t&, const ccdk::mpl::fn::inc_t&}]
  CCDK_FORCEINLINE constexpr imap(imap const& other) : ipair < Indice, Args >{ other }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:45:29: note:   candidate expects 1 argument, 2 provided
../ccdk/mpl/fusion/imap.h:42:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(Args2&& ...)
  CCDK_FORCEINLINE constexpr imap(Args2 &&... args) : ipair<Indice, Args>{ util::forward<Args2>(args) }... {  }
                             ^~~~
../ccdk/mpl/fusion/imap.h:42:29: note:   template argument deduction/substitution failed:
../ccdk/mpl/fusion/imap.h:38:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap() [with unsigned int ...Indice = {0u, 1u}; Args = {const ccdk::mpl::fn::dec_t&, const ccdk::mpl::fn::inc_t&}]
  CCDK_FORCEINLINE constexpr imap() : ipair < Indice, Args >{}... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:38:29: note:   candidate expects 0 arguments, 2 provided
In file included from test_mpl_function.cpp:22:0:
../ccdk/mpl/function/fmap.h: In instantiation of ‘constexpr ccdk::mpl::fn::fmap_t<Fn, Fs>::fmap_t(Fn&&, Fs&& ...) [with Fn = const ccdk::mpl::fn::mul_t&; Fs = {const ccdk::mpl::fn::add_t&, const ccdk::mpl::fn::sub_t&}]’:
../ccdk/mpl/util/create.h:18:53:   required from ‘constexpr auto ccdk::mpl::util::create_t<T>::operator()(Args&& ...) const [with Args = {const ccdk::mpl::fn::mul_t&, const ccdk::mpl::fn::add_t&, const ccdk::mpl::fn::sub_t&}; T = ccdk::mpl::fn::fmap_t]’
test_mpl_function.cpp:387:31:   required from here
../ccdk/mpl/function/fmap.h:23:126: error: no matching function for call to ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u>, const ccdk::mpl::fn::add_t&, const ccdk::mpl::fn::sub_t&>::imap(<brace-enclosed initializer list>)’
   CCDK_FORCEINLINE constexpr fmap_t(Fn&& inFn, Fs&&... inFs) : fn{ util::forward<Fn>(inFn) }, fs{ util::forward<Fs>(inFs)... } {}
                                                                                                                              ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:56:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> && other) : ipair < Indice, Args >{ util::move(other.template at<Indice>()) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:56:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:22:0:
../ccdk/mpl/function/fmap.h:23:126: note:   types ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u>, Args2 ...>’ and ‘const ccdk::mpl::fn::add_t’ have incompatible cv-qualifiers
   CCDK_FORCEINLINE constexpr fmap_t(Fn&& inFn, Fs&&... inFs) : fn{ util::forward<Fn>(inFn) }, fs{ util::forward<Fs>(inFs)... } {}
                                                                                                                              ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:52:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> const& other) : ipair < Indice, Args >{ other.template at<Indice>() }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:52:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:22:0:
../ccdk/mpl/function/fmap.h:23:126: note:   ‘const ccdk::mpl::fn::add_t’ is not derived from ‘const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u>, Args2 ...>’
   CCDK_FORCEINLINE constexpr fmap_t(Fn&& inFn, Fs&&... inFs) : fn{ util::forward<Fn>(inFn) }, fs{ util::forward<Fs>(inFs)... } {}
                                                                                                                              ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:48:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&&) [with unsigned int ...Indice = {0u, 1u}; Args = {const ccdk::mpl::fn::add_t&, const ccdk::mpl::fn::sub_t&}]
  CCDK_FORCEINLINE constexpr imap(imap && other) : ipair < Indice, Args >{ util::move(other) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:48:29: note:   candidate expects 1 argument, 2 provided
../ccdk/mpl/fusion/imap.h:45:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&) [with unsigned int ...Indice = {0u, 1u}; Args = {const ccdk::mpl::fn::add_t&, const ccdk::mpl::fn::sub_t&}]
  CCDK_FORCEINLINE constexpr imap(imap const& other) : ipair < Indice, Args >{ other }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:45:29: note:   candidate expects 1 argument, 2 provided
../ccdk/mpl/fusion/imap.h:42:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(Args2&& ...)
  CCDK_FORCEINLINE constexpr imap(Args2 &&... args) : ipair<Indice, Args>{ util::forward<Args2>(args) }... {  }
                             ^~~~
../ccdk/mpl/fusion/imap.h:42:29: note:   template argument deduction/substitution failed:
../ccdk/mpl/fusion/imap.h:38:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap() [with unsigned int ...Indice = {0u, 1u}; Args = {const ccdk::mpl::fn::add_t&, const ccdk::mpl::fn::sub_t&}]
  CCDK_FORCEINLINE constexpr imap() : ipair < Indice, Args >{}... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:38:29: note:   candidate expects 0 arguments, 2 provided
In file included from test_mpl_function.cpp:26:0:
../ccdk/mpl/function/val.h: In instantiation of ‘constexpr ccdk::mpl::fn::expr<ccdk::mpl::fn::value_t<T> >::expr(T2&&) [with T2 = ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u>, ccdk::mpl::fn::expr<ccdk::mpl::null_>, ccdk::mpl::fn::expr<ccdk::mpl::fn::value_t<int> > >; T = int]’:
../ccdk/mpl/fusion/pair.h:29:73:   required from ‘constexpr ccdk::mpl::fs::ipair<Key, T>::ipair(T2&&) [with T2 = ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u, 1u>, ccdk::mpl::fn::expr<ccdk::mpl::null_>, ccdk::mpl::fn::expr<ccdk::mpl::fn::value_t<int> > >; <template-parameter-2-2> = void; unsigned int Key = 1u; T = ccdk::mpl::fn::expr<ccdk::mpl::fn::value_t<int> >]’
../ccdk/mpl/fusion/imap.h:48:94:   required from ‘constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&&) [with unsigned int ...Indice = {0u, 1u}; Args = {ccdk::mpl::fn::expr<ccdk::mpl::null_>, ccdk::mpl::fn::expr<ccdk::mpl::fn::value_t<int> >}]’
../ccdk/mpl/function/expr.h:125:107:   required from ‘constexpr ccdk::mpl::fn::expr<Fn, Args ...>::expr(ccdk::mpl::fn::expr<Fn, Args ...>&&) [with Fn = ccdk::mpl::fn::invoke_t; Args = {ccdk::mpl::fn::expr<ccdk::mpl::null_>, ccdk::mpl::fn::expr<ccdk::mpl::fn::value_t<int> >}]’
../ccdk/mpl/function/expr.h:152:97:   required from ‘constexpr auto ccdk::mpl::fn::expr<ccdk::mpl::null_>::operator()(ccdk::mpl::fn::mark_lazy_t, T&&) const [with T = int]’
test_mpl_function.cpp:446:27:   required from here
../ccdk/mpl/function/val.h:28:81: error: cannot convert ‘<brace-enclosed initializer list>’ to ‘ccdk::mpl::fn::expr<ccdk::mpl::fn::value_t<int> >::value_type {aka int}’ in initialization
   CCDK_FORCEINLINE constexpr explicit expr(T2&& inT) :t{ util::forward<T2>(inT) } { DebugFunctionName(); }
                                                                                 ^
In file included from test_mpl_function.cpp:18:0:
../ccdk/mpl/function/partial.h: In instantiation of ‘ccdk::mpl::fn::partial_t<TotalSize, Fn, Ret, Args>::partial_t(Fn&&, Args&& ...) [with unsigned int TotalSize = 2u; Fn = int (&)(const ccdk::test_copy_t&, const char*); Ret = int; Args = {ccdk::test_copy_t&}]’:
../ccdk/mpl/function/partial.h:76:94:   required from ‘auto ccdk::mpl::fn::partial_create_t::partial_normal_function(ccdk::mpl::arg_pack<TArgs ...>, Fn&&, Args1&& ...) const [with Ret = int; Fn = int (&)(const ccdk::test_copy_t&, const char*); Args1 = {ccdk::test_copy_t&}; Args2 = {const ccdk::test_copy_t&, const char*}]’
../ccdk/mpl/function/partial.h:91:66:   required from ‘auto ccdk::mpl::fn::partial_create_t::partial_create_impl(ccdk::mpl::case_t<ccdk::mpl::is_function>, Fn&&, Args&& ...) const [with Fn = int (&)(const ccdk::test_copy_t&, const char*); Args = {ccdk::test_copy_t&}; ccdk::mpl::case_t<ccdk::mpl::is_function> = ccdk::mpl::tt_detail::u64x2<0ull, 4ull>]’
../ccdk/mpl/function/partial.h:118:4:   required from ‘auto ccdk::mpl::fn::partial_create_t::operator()(Fn&&, Args&& ...) const [with Fn = int (&)(const ccdk::test_copy_t&, const char*); Fn1 = int (*)(const ccdk::test_copy_t&, const char*); <template-parameter-1-3> = void; Args = {ccdk::test_copy_t&}]’
test_mpl_function.cpp:423:39:   required from here
../ccdk/mpl/function/partial.h:40:128: error: no matching function for call to ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, ccdk::test_copy_t&>::imap(<brace-enclosed initializer list>)’
   CCDK_FORCEINLINE partial_t(Fn&& inFn, Args&&... inArgs) :fn{ util::forward<Fn>(inFn) }, args{ util::forward<Args>(inArgs)... } {}
                                                                                                                                ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:56:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> && other) : ipair < Indice, Args >{ util::move(other.template at<Indice>()) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:56:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:18:0:
../ccdk/mpl/function/partial.h:40:128: note:   ‘ccdk::test_copy_t’ is not derived from ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, Args2 ...>’
   CCDK_FORCEINLINE partial_t(Fn&& inFn, Args&&... inArgs) :fn{ util::forward<Fn>(inFn) }, args{ util::forward<Args>(inArgs)... } {}
                                                                                                                                ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:52:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> const& other) : ipair < Indice, Args >{ other.template at<Indice>() }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:52:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:18:0:
../ccdk/mpl/function/partial.h:40:128: note:   ‘ccdk::test_copy_t’ is not derived from ‘const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, Args2 ...>’
   CCDK_FORCEINLINE partial_t(Fn&& inFn, Args&&... inArgs) :fn{ util::forward<Fn>(inFn) }, args{ util::forward<Args>(inArgs)... } {}
                                                                                                                                ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:48:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&&) [with unsigned int ...Indice = {0u}; Args = {ccdk::test_copy_t&}]
  CCDK_FORCEINLINE constexpr imap(imap && other) : ipair < Indice, Args >{ util::move(other) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:48:29: note:   no known conversion for argument 1 from ‘ccdk::test_copy_t’ to ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, ccdk::test_copy_t&>&&’
../ccdk/mpl/fusion/imap.h:45:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&) [with unsigned int ...Indice = {0u}; Args = {ccdk::test_copy_t&}]
  CCDK_FORCEINLINE constexpr imap(imap const& other) : ipair < Indice, Args >{ other }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:45:29: note:   no known conversion for argument 1 from ‘ccdk::test_copy_t’ to ‘const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, ccdk::test_copy_t&>&’
../ccdk/mpl/fusion/imap.h:42:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(Args2&& ...)
  CCDK_FORCEINLINE constexpr imap(Args2 &&... args) : ipair<Indice, Args>{ util::forward<Args2>(args) }... {  }
                             ^~~~
../ccdk/mpl/fusion/imap.h:42:29: note:   template argument deduction/substitution failed:
../ccdk/mpl/fusion/imap.h:38:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap() [with unsigned int ...Indice = {0u}; Args = {ccdk::test_copy_t&}]
  CCDK_FORCEINLINE constexpr imap() : ipair < Indice, Args >{}... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:38:29: note:   candidate expects 0 arguments, 1 provided
In file included from test_mpl_function.cpp:18:0:
../ccdk/mpl/function/partial.h: In instantiation of ‘ccdk::mpl::fn::partial_t<TotalSize, Fn, Ret, Args>::partial_t(Fn&&, Args&& ...) [with unsigned int TotalSize = 2u; Fn = int (*&)(const ccdk::test_copy_t&, const char*); Ret = int; Args = {ccdk::test_copy_t&}]’:
../ccdk/mpl/function/partial.h:76:94:   required from ‘auto ccdk::mpl::fn::partial_create_t::partial_normal_function(ccdk::mpl::arg_pack<TArgs ...>, Fn&&, Args1&& ...) const [with Ret = int; Fn = int (*&)(const ccdk::test_copy_t&, const char*); Args1 = {ccdk::test_copy_t&}; Args2 = {const ccdk::test_copy_t&, const char*}]’
../ccdk/mpl/function/partial.h:91:66:   required from ‘auto ccdk::mpl::fn::partial_create_t::partial_create_impl(ccdk::mpl::case_t<ccdk::mpl::is_function>, Fn&&, Args&& ...) const [with Fn = int (*)(const ccdk::test_copy_t&, const char*); Args = {ccdk::test_copy_t&}; ccdk::mpl::case_t<ccdk::mpl::is_function> = ccdk::mpl::tt_detail::u64x2<0ull, 4ull>]’
../ccdk/mpl/function/partial.h:118:4:   required from ‘auto ccdk::mpl::fn::partial_create_t::operator()(Fn&&, Args&& ...) const [with Fn = int (*)(const ccdk::test_copy_t&, const char*); Fn1 = int (*)(const ccdk::test_copy_t&, const char*); <template-parameter-1-3> = void; Args = {ccdk::test_copy_t&}]’
test_mpl_function.cpp:424:40:   required from here
../ccdk/mpl/function/partial.h:40:128: error: no matching function for call to ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, ccdk::test_copy_t&>::imap(<brace-enclosed initializer list>)’
   CCDK_FORCEINLINE partial_t(Fn&& inFn, Args&&... inArgs) :fn{ util::forward<Fn>(inFn) }, args{ util::forward<Args>(inArgs)... } {}
                                                                                                                                ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:56:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> && other) : ipair < Indice, Args >{ util::move(other.template at<Indice>()) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:56:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:18:0:
../ccdk/mpl/function/partial.h:40:128: note:   ‘ccdk::test_copy_t’ is not derived from ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, Args2 ...>’
   CCDK_FORCEINLINE partial_t(Fn&& inFn, Args&&... inArgs) :fn{ util::forward<Fn>(inFn) }, args{ util::forward<Args>(inArgs)... } {}
                                                                                                                                ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:52:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args2 ...>&)
  CCDK_FORCEINLINE constexpr imap(imap<indice_pack<Indice...>, Args2...> const& other) : ipair < Indice, Args >{ other.template at<Indice>() }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:52:29: note:   template argument deduction/substitution failed:
In file included from test_mpl_function.cpp:18:0:
../ccdk/mpl/function/partial.h:40:128: note:   ‘ccdk::test_copy_t’ is not derived from ‘const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, Args2 ...>’
   CCDK_FORCEINLINE partial_t(Fn&& inFn, Args&&... inArgs) :fn{ util::forward<Fn>(inFn) }, args{ util::forward<Args>(inArgs)... } {}
                                                                                                                                ^
In file included from ../ccdk/mpl/fusion/tuple.h:12:0,
                 from ../ccdk/mpl/type_traits.h:35,
                 from test_mpl_function.cpp:10:
../ccdk/mpl/fusion/imap.h:48:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&&) [with unsigned int ...Indice = {0u}; Args = {ccdk::test_copy_t&}]
  CCDK_FORCEINLINE constexpr imap(imap && other) : ipair < Indice, Args >{ util::move(other) }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:48:29: note:   no known conversion for argument 1 from ‘ccdk::test_copy_t’ to ‘ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, ccdk::test_copy_t&>&&’
../ccdk/mpl/fusion/imap.h:45:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>&) [with unsigned int ...Indice = {0u}; Args = {ccdk::test_copy_t&}]
  CCDK_FORCEINLINE constexpr imap(imap const& other) : ipair < Indice, Args >{ other }... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:45:29: note:   no known conversion for argument 1 from ‘ccdk::test_copy_t’ to ‘const ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, 0u>, ccdk::test_copy_t&>&’
../ccdk/mpl/fusion/imap.h:42:29: note: candidate: template<class ... Args2, class> constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap(Args2&& ...)
  CCDK_FORCEINLINE constexpr imap(Args2 &&... args) : ipair<Indice, Args>{ util::forward<Args2>(args) }... {  }
                             ^~~~
../ccdk/mpl/fusion/imap.h:42:29: note:   template argument deduction/substitution failed:
../ccdk/mpl/fusion/imap.h:38:29: note: candidate: constexpr ccdk::mpl::fs::imap<ccdk::mpl::val_pack<unsigned int, indice ...>, Args ...>::imap() [with unsigned int ...Indice = {0u}; Args = {ccdk::test_copy_t&}]
  CCDK_FORCEINLINE constexpr imap() : ipair < Indice, Args >{}... {}
                             ^~~~
../ccdk/mpl/fusion/imap.h:38:29: note:   candidate expects 0 arguments, 1 provided
