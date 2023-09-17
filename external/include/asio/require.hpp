//
// require.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_REQUIRE_HPP
#define ASIO_REQUIRE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "detail/config.hpp"
#include "detail/type_traits.hpp"
#include "is_applicable_property.hpp"
#include "traits/require_member.hpp"
#include "traits/require_free.hpp"
#include "traits/static_require.hpp"

#include "detail/push_options.hpp"

#if defined(GENERATING_DOCUMENTATION)

namespace asio {

/// A customisation point that applies a concept-preserving property to an
/// object.
/**
 * The name <tt>require</tt> denotes a customisation point object. The
 * expression <tt>asio::require(E, P0, Pn...)</tt> for some
 * subexpressions <tt>E</tt> and <tt>P0</tt>, and where <tt>Pn...</tt>
 * represents <tt>N</tt> subexpressions (where <tt>N</tt> is 0 or more, and with
 * types <tt>T = decay_t<decltype(E)></tt> and <tt>Prop0 =
 * decay_t<decltype(P0)></tt>) is expression-equivalent to:
 *
 * @li If <tt>is_applicable_property_v<T, Prop0> && Prop0::is_requirable</tt> is
 *   not a well-formed constant expression with value <tt>true</tt>,
 *   <tt>asio::require(E, P0, Pn...)</tt> is ill-formed.
 *
 * @li Otherwise, <tt>E</tt> if <tt>N == 0</tt> and the expression
 *   <tt>Prop0::template static_query_v<T> == Prop0::value()</tt> is a
 *   well-formed constant expression with value <tt>true</tt>.
 *
 * @li Otherwise, <tt>(E).require(P0)</tt> if <tt>N == 0</tt> and the expression
 *   <tt>(E).require(P0)</tt> is a valid expression.
 *
 * @li Otherwise, <tt>require(E, P0)</tt> if <tt>N == 0</tt> and the expression
 *   <tt>require(E, P0)</tt> is a valid expression with overload resolution
 *   performed in a context that does not include the declaration of the
 *   <tt>require</tt> customization point object.
 *
 * @li Otherwise,
 *   <tt>asio::require(asio::require(E, P0), Pn...)</tt>
 *   if <tt>N > 0</tt> and the expression
 *   <tt>asio::require(asio::require(E, P0), Pn...)</tt>
 *   is a valid expression.
 *
 * @li Otherwise, <tt>asio::require(E, P0, Pn...)</tt> is ill-formed.
 */
inline constexpr unspecified require = unspecified;

/// A type trait that determines whether a @c require expression is well-formed.
/**
 * Class template @c can_require is a trait that is derived from
 * @c true_type if the expression <tt>asio::require(std::declval<T>(),
 * std::declval<Properties>()...)</tt> is well formed; otherwise @c false_type.
 */
template <typename T, typename... Properties>
struct can_require :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines whether a @c require expression will not throw.
/**
 * Class template @c is_nothrow_require is a trait that is derived from
 * @c true_type if the expression <tt>asio::require(std::declval<T>(),
 * std::declval<Properties>()...)</tt> is @c noexcept; otherwise @c false_type.
 */
template <typename T, typename... Properties>
struct is_nothrow_require :
  integral_constant<bool, automatically_determined>
{
};

/// A type trait that determines the result type of a @c require expression.
/**
 * Class template @c require_result is a trait that determines the result
 * type of the expression <tt>asio::require(std::declval<T>(),
 * std::declval<Properties>()...)</tt>.
 */
template <typename T, typename... Properties>
struct require_result
{
  /// The result of the @c require expression.
  typedef automatically_determined type;
};

} // namespace asio

#else // defined(GENERATING_DOCUMENTATION)

namespace asio_require_fn {

using asio::conditional;
using asio::decay;
using asio::declval;
using asio::enable_if;
using asio::is_applicable_property;
using asio::traits::require_free;
using asio::traits::require_member;
using asio::traits::static_require;

void require();

enum overload_type
{
  identity,
  call_member,
  call_free,
  two_props,
  n_props,
  ill_formed
};

template <typename Impl, typename T, typename Properties, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct call_traits
{
  ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
  ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

template <typename Impl, typename T, typename Property>
struct call_traits<Impl, T, void(Property),
  typename enable_if<
    is_applicable_property<
      typename decay<T>::type,
      typename decay<Property>::type
    >::value
  >::type,
  typename enable_if<
    decay<Property>::type::is_requirable
  >::type,
  typename enable_if<
    static_require<T, Property>::is_valid
  >::type>
{
  ASIO_STATIC_CONSTEXPR(overload_type, overload = identity);
  ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

#if defined(ASIO_HAS_MOVE)
  typedef ASIO_MOVE_ARG(T) result_type;
#else // defined(ASIO_HAS_MOVE)
  typedef ASIO_MOVE_ARG(typename decay<T>::type) result_type;
#endif // defined(ASIO_HAS_MOVE)
};

template <typename Impl, typename T, typename Property>
struct call_traits<Impl, T, void(Property),
  typename enable_if<
    is_applicable_property<
      typename decay<T>::type,
      typename decay<Property>::type
    >::value
  >::type,
  typename enable_if<
    decay<Property>::type::is_requirable
  >::type,
  typename enable_if<
    !static_require<T, Property>::is_valid
  >::type,
  typename enable_if<
    require_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type> :
  require_member<typename Impl::template proxy<T>::type, Property>
{
  ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename Impl, typename T, typename Property>
struct call_traits<Impl, T, void(Property),
  typename enable_if<
    is_applicable_property<
      typename decay<T>::type,
      typename decay<Property>::type
    >::value
  >::type,
  typename enable_if<
    decay<Property>::type::is_requirable
  >::type,
  typename enable_if<
    !static_require<T, Property>::is_valid
  >::type,
  typename enable_if<
    !require_member<typename Impl::template proxy<T>::type, Property>::is_valid
  >::type,
  typename enable_if<
    require_free<T, Property>::is_valid
  >::type> :
  require_free<T, Property>
{
  ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

template <typename Impl, typename T, typename P0, typename P1>
struct call_traits<Impl, T, void(P0, P1),
  typename enable_if<
    call_traits<Impl, T, void(P0)>::overload != ill_formed
  >::type,
  typename enable_if<
    call_traits<
      Impl,
      typename call_traits<Impl, T, void(P0)>::result_type,
      void(P1)
    >::overload != ill_formed
  >::type>
{
  ASIO_STATIC_CONSTEXPR(overload_type, overload = two_props);

  ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (
      call_traits<Impl, T, void(P0)>::is_noexcept
      &&
      call_traits<
        Impl,
        typename call_traits<Impl, T, void(P0)>::result_type,
        void(P1)
      >::is_noexcept
    ));

  typedef typename decay<
    typename call_traits<
      Impl,
      typename call_traits<Impl, T, void(P0)>::result_type,
      void(P1)
    >::result_type
  >::type result_type;
};

template <typename Impl, typename T, typename P0,
    typename P1, typename ASIO_ELLIPSIS PN>
struct call_traits<Impl, T, void(P0, P1, PN ASIO_ELLIPSIS),
  typename enable_if<
    call_traits<Impl, T, void(P0)>::overload != ill_formed
  >::type,
  typename enable_if<
    call_traits<
      Impl,
      typename call_traits<Impl, T, void(P0)>::result_type,
      void(P1, PN ASIO_ELLIPSIS)
    >::overload != ill_formed
  >::type>
{
  ASIO_STATIC_CONSTEXPR(overload_type, overload = n_props);

  ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    (
      call_traits<Impl, T, void(P0)>::is_noexcept
      &&
      call_traits<
        Impl,
        typename call_traits<Impl, T, void(P0)>::result_type,
        void(P1, PN ASIO_ELLIPSIS)
      >::is_noexcept
    ));

  typedef typename decay<
    typename call_traits<
      Impl,
      typename call_traits<Impl, T, void(P0)>::result_type,
      void(P1, PN ASIO_ELLIPSIS)
    >::result_type
  >::type result_type;
};

struct impl
{
  template <typename T>
  struct proxy
  {
#if defined(ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)
    struct type
    {
      template <typename P>
      auto require(ASIO_MOVE_ARG(P) p)
        noexcept(
          noexcept(
            declval<typename conditional<true, T, P>::type>().require(
              ASIO_MOVE_CAST(P)(p))
          )
        )
        -> decltype(
          declval<typename conditional<true, T, P>::type>().require(
            ASIO_MOVE_CAST(P)(p))
        );
    };
#else // defined(ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)
    typedef T type;
#endif // defined(ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)
  };

  template <typename T, typename Property>
  ASIO_NODISCARD ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(Property)>::overload == identity,
    typename call_traits<impl, T, void(Property)>::result_type
  >::type
  operator()(
      ASIO_MOVE_ARG(T) t,
      ASIO_MOVE_ARG(Property)) const
    ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(Property)>::is_noexcept))
  {
    return ASIO_MOVE_CAST(T)(t);
  }

  template <typename T, typename Property>
  ASIO_NODISCARD ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(Property)>::overload == call_member,
    typename call_traits<impl, T, void(Property)>::result_type
  >::type
  operator()(
      ASIO_MOVE_ARG(T) t,
      ASIO_MOVE_ARG(Property) p) const
    ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(Property)>::is_noexcept))
  {
    return ASIO_MOVE_CAST(T)(t).require(
        ASIO_MOVE_CAST(Property)(p));
  }

  template <typename T, typename Property>
  ASIO_NODISCARD ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(Property)>::overload == call_free,
    typename call_traits<impl, T, void(Property)>::result_type
  >::type
  operator()(
      ASIO_MOVE_ARG(T) t,
      ASIO_MOVE_ARG(Property) p) const
    ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(Property)>::is_noexcept))
  {
    return require(
        ASIO_MOVE_CAST(T)(t),
        ASIO_MOVE_CAST(Property)(p));
  }

  template <typename T, typename P0, typename P1>
  ASIO_NODISCARD ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(P0, P1)>::overload == two_props,
    typename call_traits<impl, T, void(P0, P1)>::result_type
  >::type
  operator()(
      ASIO_MOVE_ARG(T) t,
      ASIO_MOVE_ARG(P0) p0,
      ASIO_MOVE_ARG(P1) p1) const
    ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(P0, P1)>::is_noexcept))
  {
    return (*this)(
        (*this)(
          ASIO_MOVE_CAST(T)(t),
          ASIO_MOVE_CAST(P0)(p0)),
        ASIO_MOVE_CAST(P1)(p1));
  }

  template <typename T, typename P0, typename P1,
    typename ASIO_ELLIPSIS PN>
  ASIO_NODISCARD ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T,
      void(P0, P1, PN ASIO_ELLIPSIS)>::overload == n_props,
    typename call_traits<impl, T,
      void(P0, P1, PN ASIO_ELLIPSIS)>::result_type
  >::type
  operator()(
      ASIO_MOVE_ARG(T) t,
      ASIO_MOVE_ARG(P0) p0,
      ASIO_MOVE_ARG(P1) p1,
      ASIO_MOVE_ARG(PN) ASIO_ELLIPSIS pn) const
    ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(P0, P1, PN ASIO_ELLIPSIS)>::is_noexcept))
  {
    return (*this)(
        (*this)(
          ASIO_MOVE_CAST(T)(t),
          ASIO_MOVE_CAST(P0)(p0)),
        ASIO_MOVE_CAST(P1)(p1),
        ASIO_MOVE_CAST(PN)(pn) ASIO_ELLIPSIS);
  }
};

template <typename T = impl>
struct static_instance
{
  static const T instance;
};

template <typename T>
const T static_instance<T>::instance = {};

} // namespace asio_require_fn
namespace asio {
namespace {

static ASIO_CONSTEXPR const asio_require_fn::impl&
  require = asio_require_fn::static_instance<>::instance;

} // namespace

typedef asio_require_fn::impl require_t;

#if defined(ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Properties>
struct can_require :
  integral_constant<bool,
    asio_require_fn::call_traits<
      require_t, T, void(Properties...)>::overload
        != asio_require_fn::ill_formed>
{
};

#else // defined(ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename P0 = void,
    typename P1 = void, typename P2 = void>
struct can_require :
  integral_constant<bool,
    asio_require_fn::call_traits<require_t, T, void(P0, P1, P2)>::overload
      != asio_require_fn::ill_formed>
{
};

template <typename T, typename P0, typename P1>
struct can_require<T, P0, P1> :
  integral_constant<bool,
    asio_require_fn::call_traits<require_t, T, void(P0, P1)>::overload
      != asio_require_fn::ill_formed>
{
};

template <typename T, typename P0>
struct can_require<T, P0> :
  integral_constant<bool,
    asio_require_fn::call_traits<require_t, T, void(P0)>::overload
      != asio_require_fn::ill_formed>
{
};

template <typename T>
struct can_require<T> :
  false_type
{
};

#endif // defined(ASIO_HAS_VARIADIC_TEMPLATES)

#if defined(ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename ASIO_ELLIPSIS Properties>
constexpr bool can_require_v
  = can_require<T, Properties ASIO_ELLIPSIS>::value;

#endif // defined(ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Properties>
struct is_nothrow_require :
  integral_constant<bool,
    asio_require_fn::call_traits<
      require_t, T, void(Properties...)>::is_noexcept>
{
};

#else // defined(ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename P0 = void,
    typename P1 = void, typename P2 = void>
struct is_nothrow_require :
  integral_constant<bool,
    asio_require_fn::call_traits<
      require_t, T, void(P0, P1, P2)>::is_noexcept>
{
};

template <typename T, typename P0, typename P1>
struct is_nothrow_require<T, P0, P1> :
  integral_constant<bool,
    asio_require_fn::call_traits<
      require_t, T, void(P0, P1)>::is_noexcept>
{
};

template <typename T, typename P0>
struct is_nothrow_require<T, P0> :
  integral_constant<bool,
    asio_require_fn::call_traits<
      require_t, T, void(P0)>::is_noexcept>
{
};

template <typename T>
struct is_nothrow_require<T> :
  false_type
{
};

#endif // defined(ASIO_HAS_VARIADIC_TEMPLATES)

#if defined(ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename ASIO_ELLIPSIS Properties>
constexpr bool is_nothrow_require_v
  = is_nothrow_require<T, Properties ASIO_ELLIPSIS>::value;

#endif // defined(ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Properties>
struct require_result
{
  typedef typename asio_require_fn::call_traits<
      require_t, T, void(Properties...)>::result_type type;
};

#else // defined(ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename P0 = void,
    typename P1 = void, typename P2 = void>
struct require_result
{
  typedef typename asio_require_fn::call_traits<
      require_t, T, void(P0, P1, P2)>::result_type type;
};

template <typename T, typename P0, typename P1>
struct require_result<T, P0, P1>
{
  typedef typename asio_require_fn::call_traits<
      require_t, T, void(P0, P1)>::result_type type;
};

template <typename T, typename P0>
struct require_result<T, P0>
{
  typedef typename asio_require_fn::call_traits<
      require_t, T, void(P0)>::result_type type;
};

template <typename T>
struct require_result<T>
{
};

#endif // defined(ASIO_HAS_VARIADIC_TEMPLATES)

} // namespace asio

#endif // defined(GENERATING_DOCUMENTATION)

#include "detail/pop_options.hpp"

#endif // ASIO_REQUIRE_HPP