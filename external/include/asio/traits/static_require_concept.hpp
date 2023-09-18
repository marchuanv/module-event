//
// traits/static_require_concept.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_TRAITS_STATIC_REQUIRE_CONCEPT_HPP
#define ASIO_TRAITS_STATIC_REQUIRE_CONCEPT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../detail/config.hpp"
#include "../detail/type_traits.hpp"
#include "../traits/static_query.hpp"

#if defined(ASIO_HAS_DECLTYPE) \
  && defined(ASIO_HAS_NOEXCEPT)
# define ASIO_HAS_DEDUCED_STATIC_REQUIRE_CONCEPT_TRAIT 1
#endif // defined(ASIO_HAS_DECLTYPE)
       //   && defined(ASIO_HAS_NOEXCEPT)

#include "../detail/push_options.hpp"

namespace asio {
namespace traits {

template <typename T, typename Property, typename = void>
struct static_require_concept_default;

template <typename T, typename Property, typename = void>
struct static_require_concept;

} // namespace traits
namespace detail {

struct no_static_require_concept
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
};

template <typename T, typename Property, typename = void>
struct static_require_concept_trait :
  conditional<
    is_same<T, typename decay<T>::type>::value
      && is_same<Property, typename decay<Property>::type>::value,
    no_static_require_concept,
    traits::static_require_concept<
      typename decay<T>::type,
      typename decay<Property>::type>
  >::type
{
};

#if defined(ASIO_HAS_DEDUCED_STATIC_REQUIRE_CONCEPT_TRAIT)

#if defined(ASIO_HAS_WORKING_EXPRESSION_SFINAE)

template <typename T, typename Property>
struct static_require_concept_trait<T, Property,
  typename enable_if<
    decay<Property>::type::value() == traits::static_query<T, Property>::value()
  >::type>
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
};

#else // defined(ASIO_HAS_WORKING_EXPRESSION_SFINAE)

false_type static_require_concept_test(...);

template <typename T, typename Property>
true_type static_require_concept_test(T*, Property*,
    typename enable_if<
      Property::value() == traits::static_query<T, Property>::value()
    >::type* = 0);

template <typename T, typename Property>
struct has_static_require_concept
{
  ASIO_STATIC_CONSTEXPR(bool, value =
    decltype((static_require_concept_test)(
      static_cast<T*>(0), static_cast<Property*>(0)))::value);
};

template <typename T, typename Property>
struct static_require_concept_trait<T, Property,
  typename enable_if<
    has_static_require_concept<typename decay<T>::type,
      typename decay<Property>::type>::value
  >::type>
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
};

#endif // defined(ASIO_HAS_WORKING_EXPRESSION_SFINAE)

#endif // defined(ASIO_HAS_DEDUCED_STATIC_REQUIRE_CONCEPT_TRAIT)

} // namespace detail
namespace traits {

template <typename T, typename Property, typename>
struct static_require_concept_default :
  detail::static_require_concept_trait<T, Property>
{
};

template <typename T, typename Property, typename>
struct static_require_concept : static_require_concept_default<T, Property>
{
};

} // namespace traits
} // namespace asio

#include "../detail/pop_options.hpp"

#endif // ASIO_TRAITS_STATIC_REQUIRE_CONCEPT_HPP
