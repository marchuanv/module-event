//
// experimental/as_tuple.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_EXPERIMENTAL_AS_TUPLE_HPP
#define ASIO_EXPERIMENTAL_AS_TUPLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../detail/config.hpp"
#include "../as_tuple.hpp"

#include "../detail/push_options.hpp"

namespace asio {
namespace experimental {

#if !defined(ASIO_NO_DEPRECATED)
using asio::as_tuple_t;
using asio::as_tuple;
#endif // !defined(ASIO_NO_DEPRECATED)

} // namespace experimental
} // namespace asio

#include "../detail/pop_options.hpp"

#endif // ASIO_EXPERIMENTAL_AS_TUPLE_HPP
