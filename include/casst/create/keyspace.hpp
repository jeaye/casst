#pragma once

#include <casst/types.hpp>
#include <casst/create/detail/keyspace.hpp>
#include <casst/create/policy.hpp>

namespace casst
{
  namespace create
  {
    template <typename Policy = overwrite>
    auto keyspace(std::string const &name)
    { return detail::keyspace<detail::steps::base>{ name, Policy{} }; }

    inline auto keyspace_if_not_exists(std::string const &name)
    { return detail::keyspace<detail::steps::base>{ name, if_not_exists{} }; }

    inline auto replication_factor(std::size_t const factor)
    { return detail::replication_factor{ factor }; }

    inline auto data_center(std::string const &name, std::size_t const replicas)
    { return detail::data_center{ name, replicas }; }
  }
}
