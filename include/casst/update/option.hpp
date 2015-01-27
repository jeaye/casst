#pragma once

#include <casst/detail/types.hpp>

#include <string>

namespace casst
{
  namespace option
  {
    inline std::string timestamp(timestamp_t const time)
    { return "TIMESTAMP " + std::to_string(time); }
    inline std::string ttl(timestamp_t const time)
    { return "TTL " + std::to_string(time); }
  }
}
