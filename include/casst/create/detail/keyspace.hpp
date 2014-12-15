#pragma once

#include <jeayeson/jeayeson.hpp>
#include <casst/types.hpp>

namespace casst
{
  namespace create
  {
    struct overwrite
    { static char constexpr const * const value{ "" }; };
    struct if_not_exists
    { static char constexpr const * const value{ "IF NOT EXISTS " }; };

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
        string name;
        std::size_t replicas;
      };

      enum class steps
      {
        base,
        with_replication
      };

      template <steps S>
      class blob
      { };

      template <>
      class blob<steps::with_replication>
      {
        public:
          blob(ostream &&oss, simple_strategy const, replication_factor const rf)
            : oss_{ std::move(oss) }
          {
            map_["class"] = "SimpleStrategy";
            map_["replication_factor"] = rf.factor;

            oss_ << "WITH REPLICATION = " << map_ << " ";
          }

          template <typename... DBs>
          blob(ostream &&oss, network_topology_strategy const, DBs &&...dbs)
            : oss_{ std::move(oss) }
          {
            map_["class"] = "NetworkTopologyStrategy";

            int _[]{ (map_[dbs.name] = dbs.replicas, 0)... };
            static_cast<void>(_);

            oss_ << "WITH REPLICATION = " << map_ << " ";
          }

          blob& and_durable_writes(bool const b)
          {
            oss_ << "AND DURABLE_WRITES = " << std::boolalpha << b << " ";
            return *this;
          }

          std::string to_string() const
          { return oss_.str(); }

        private:
          json_map map_;
          ostream oss_;
      };

      template <>
      class blob<steps::base>
      {
        public:
          template <typename Policy>
          blob(string const &name, Policy)
            : name_{ name }
            , policy_{ Policy::value }
          { }

          template <typename Strategy, typename... Args>
          blob<steps::with_replication> with_replication(Args &&...args)
          {
            static_assert(std::is_same<Strategy, simple_strategy>::value ||
                          std::is_same<Strategy, network_topology_strategy>::value,
                          "invalid replication strategy");

            ostream oss;
            oss << "CREATE KEYSPACE " << policy_ << name_ << " ";
            return { std::move(oss), Strategy{}, std::forward<Args>(args)... };
          }

          blob<steps::with_replication> with_replication_simple(replication_factor const rf)
          { return with_replication<simple_strategy>(rf); }

          template <typename... DBs>
          blob<steps::with_replication> with_replication_network_topology(DBs &&...dbs)
          { return with_replication<network_topology_strategy>(std::forward<DBs>(dbs)...); }

        private:
          string const name_, policy_;
      };
    }
  }
}
