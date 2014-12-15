#pragma once

#include <casst/types.hpp>
#include <casst/create/detail/keyspace.hpp>

namespace casst
{
  namespace create
  {
    template <typename Policy = overwrite>
    auto keyspace(string const &name)
    { return detail::blob<detail::steps::base>{ name, Policy{} }; }

    auto replication_factor(std::size_t const factor)
    { return detail::replication_factor{ factor }; }

    auto data_center(string const &name, std::size_t const replicas)
    { return detail::data_center{ name, replicas }; }
  }
}
