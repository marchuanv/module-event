//
// ip/bad_address_cast.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_IP_BAD_ADDRESS_CAST_HPP
#define ASIO_IP_BAD_ADDRESS_CAST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "detail/config.hpp"
#include <typeinfo>

#include "detail/push_options.hpp"

namespace asio {
namespace ip {

/// Thrown to indicate a failed address conversion.
class bad_address_cast :
#if defined(ASIO_MSVC) && defined(_HAS_EXCEPTIONS) && !_HAS_EXCEPTIONS
  public std::exception
#else
  public std::bad_cast
#endif
{
public:
  /// Default constructor.
  bad_address_cast() {}

  /// Copy constructor.
  bad_address_cast(const bad_address_cast& other) ASIO_NOEXCEPT_OR_NOTHROW
#if defined(ASIO_MSVC) && defined(_HAS_EXCEPTIONS) && !_HAS_EXCEPTIONS
    : std::exception(static_cast<const std::exception&>(other))
#else
    : std::bad_cast(static_cast<const std::bad_cast&>(other))
#endif
  {
  }

  /// Destructor.
  virtual ~bad_address_cast() ASIO_NOEXCEPT_OR_NOTHROW {}

  /// Get the message associated with the exception.
  virtual const char* what() const ASIO_NOEXCEPT_OR_NOTHROW
  {
    return "bad address cast";
  }
};

} // namespace ip
} // namespace asio

#include "detail/pop_options.hpp"

#endif // ASIO_IP_ADDRESS_HPP
