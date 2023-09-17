//
// execution.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_EXECUTION_HPP
#define ASIO_EXECUTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "execution/allocator.hpp"
#include "execution/any_executor.hpp"
#include "execution/bad_executor.hpp"
#include "execution/blocking.hpp"
#include "execution/blocking_adaptation.hpp"
#include "execution/bulk_execute.hpp"
#include "execution/bulk_guarantee.hpp"
#include "execution/connect.hpp"
#include "execution/context.hpp"
#include "execution/context_as.hpp"
#include "execution/execute.hpp"
#include "execution/executor.hpp"
#include "execution/invocable_archetype.hpp"
#include "execution/mapping.hpp"
#include "execution/occupancy.hpp"
#include "execution/operation_state.hpp"
#include "execution/outstanding_work.hpp"
#include "execution/prefer_only.hpp"
#include "execution/receiver.hpp"
#include "execution/receiver_invocation_error.hpp"
#include "execution/relationship.hpp"
#include "execution/schedule.hpp"
#include "execution/scheduler.hpp"
#include "execution/sender.hpp"
#include "execution/set_done.hpp"
#include "execution/set_error.hpp"
#include "execution/set_value.hpp"
#include "execution/start.hpp"
#include "execution/submit.hpp"

#endif // ASIO_EXECUTION_HPP
