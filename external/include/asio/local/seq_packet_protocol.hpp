//
// local/seq_packet_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_LOCAL_SEQ_PACKET_PROTOCOL_HPP
#define ASIO_LOCAL_SEQ_PACKET_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../detail/config.hpp"

#if defined(ASIO_HAS_LOCAL_SOCKETS) \
  || defined(GENERATING_DOCUMENTATION)

#include "../basic_socket_acceptor.hpp"
#include "../basic_seq_packet_socket.hpp"
#include "../detail/socket_types.hpp"
#include "basic_endpoint.hpp"

#include "../detail/push_options.hpp"

namespace asio {
namespace local {

/// Encapsulates the flags needed for seq_packet UNIX sockets.
/**
 * The asio::local::seq_packet_protocol class contains flags necessary
 * for sequenced packet UNIX domain sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class seq_packet_protocol
{
public:
  /// Obtain an identifier for the type of the protocol.
  int type() const ASIO_NOEXCEPT
  {
    return SOCK_SEQPACKET;
  }

  /// Obtain an identifier for the protocol.
  int protocol() const ASIO_NOEXCEPT
  {
    return 0;
  }

  /// Obtain an identifier for the protocol family.
  int family() const ASIO_NOEXCEPT
  {
    return AF_UNIX;
  }

  /// The type of a UNIX domain endpoint.
  typedef basic_endpoint<seq_packet_protocol> endpoint;

  /// The UNIX domain socket type.
  typedef basic_seq_packet_socket<seq_packet_protocol> socket;

  /// The UNIX domain acceptor type.
  typedef basic_socket_acceptor<seq_packet_protocol> acceptor;
};

} // namespace local
} // namespace asio

#include "../detail/pop_options.hpp"

#endif // defined(ASIO_HAS_LOCAL_SOCKETS)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // ASIO_LOCAL_SEQ_PACKET_PROTOCOL_HPP
