#pragma once

#include <casst/datatypes.hpp>
#include <casst/json/map.hpp>
#include <casst/detail/types.hpp>

#include <sstream>

namespace casst
{
  namespace create
  {
    struct simple_strategy
    { };
    struct network_topology_strategy
    { };

    namespace detail
    {
      struct replication_factor
      { std::size_t factor; };
      struct data_center
      {
        std::string name;
        std::size_t replicas;
      };

      enum class steps
      {
        base,
        with_replication
      };

      template <steps S>
      class keyspace;

      template <>
      class keyspace<steps::with_replication>
      {
        public:
          keyspace(ostringstream &&oss, simple_strategy const,
                   replication_factor const rf)
            : oss_{ std::move(oss) }
          {
            oss_ << "WITH REPLICATION = "
                 << json::map
                 {
                   { "class", "SimpleStrategy" },
                   { "replication_factor", rf.factor }
                 }
                 << " ";
          }

          template <typename... DBs>
          keyspace(ostringstream &&oss, network_topology_strategy const,
                   DBs &&...dbs)
            : oss_{ std::move(oss) }
          {
            oss_ << "WITH REPLICATION = "
                 << json::map
                 {
                   { "class", "NetworkTopologyStrategy" },
                   { dbs.name, dbs.replicas }...
                 }
                 << " ";
          }

          keyspace& and_durable_writes(bool const b)
          {
            oss_ << "AND DURABLE_WRITES = " << std::boolalpha << b << " ";
            return *this;
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          json::map map_;
          ostringstream oss_;
      };

      template <>
      class keyspace<steps::base>
      {
        public:
          template <typename Policy>
          keyspace(std::string const &name, Policy)
            : name_{ name }
            , policy_{ Policy::value }
          { }

          template <typename Strategy, typename... Args>
          keyspace<steps::with_replication> with_replication(Args &&...args)
          {
            static_assert(std::is_same<Strategy, simple_strategy>::value ||
                          std::is_same<Strategy, network_topology_strategy>::value,
                          "invalid replication strategy");

            ostringstream oss;
            oss << "CREATE KEYSPACE " << policy_ << name_ << " ";
            return { std::move(oss), Strategy{}, std::forward<Args>(args)... };
          }

          keyspace<steps::with_replication> with_replication_simple(
                                              replication_factor const rf)
          { return with_replication<simple_strategy>(rf); }

          template <typename... DBs>
          keyspace<steps::with_replication> with_replication_network_topology(
                                              DBs &&...dbs)
          { return with_replication<network_topology_strategy>(
                    std::forward<DBs>(dbs)...); }

        private:
          std::string const name_, policy_;
      };
    }
  }
}
