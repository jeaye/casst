#pragma once

#include <string>

namespace casst
{
  inline auto alias(std::string const &lhs, std::string const &rhs)
  { return lhs + " AS " + rhs; }

  inline auto writetime(std::string const &name)
  { return "WRITETIME( " + name + " )"; }

  inline auto ttl(std::string const &name)
  { return "TTL( " + name + " )"; }
}
