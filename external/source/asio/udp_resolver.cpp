/*!
    \file udp_resolver.cpp
    \brief UDP resolver implementation
    \author Ivan Shynkarenka
    \date 08.02.2019
    \copyright MIT License
*/

#include "asio/udp_resolver.h"

namespace CppServer {
namespace Asio {

UDPResolver::UDPResolver(const std::shared_ptr<Service>& service)
    : _service(service),
      _io_service(_service->GetAsioService()),
      _strand(*_io_service),
      _strand_required(_service->IsStrandRequired()),
      _resolver(*_io_service)
{
    assert((service != nullptr) && "Asio service is invalid!");
    if (service == nullptr)
        throw CppCommon::ArgumentException("Asio service is invalid!");
}

} // namespace Asio
} // namespace CppServer
