#pragma once

#include <casst/types.hpp>
#include <casst/create/policy.hpp>
#include <casst/create/detail/table.hpp>

namespace casst
{
  namespace create
  {
    template <typename Policy = overwrite>
    auto table(std::string const &name)
    { return detail::table<detail::steps::base>{ name, Policy{} }; }

    auto table_if_not_exists(std::string const &name)
    { return detail::table<detail::steps::base>{ name, if_not_exists{} }; }
  }
}
