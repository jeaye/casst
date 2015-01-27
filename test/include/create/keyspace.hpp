#pragma once

#include <jest/jest.hpp>

#include <casst/create/keyspace.hpp>

namespace casst
{
  struct create_keyspace_test{};
  using create_keyspace_group = jest::group<create_keyspace_test>;
  static create_keyspace_group const create_keyspace_obj{ "create_keyspace" };
}

namespace jest
{
  template <> template <>
  void casst::create_keyspace_group::test<0>() /* base */
  {
    casst::create::keyspace<casst::create::if_not_exists>("cmb_tables");
    casst::create::keyspace("cmb_tables");
    casst::create::keyspace_if_not_exists("cmb_tables");
  }
  
  template <> template <>
  void casst::create_keyspace_group::test<1>() /* with_replication */
  {
    expect_equal
    (
      casst::create::keyspace("cmb_tables").
        with_replication_simple(casst::create::replication_factor(1)).
        to_string(),

      "CREATE KEYSPACE cmb_tables WITH REPLICATION = "
      "{ 'class': 'SimpleStrategy', 'replication_factor': 1 } "
    );
  }
  
  template <> template <>
  void casst::create_keyspace_group::test<2>() /* with_replication if_not_exists */
  {
    expect_equal
    (
      casst::create::keyspace_if_not_exists("cmb_tables").
        with_replication_simple(casst::create::replication_factor(1)).
        to_string(),

      "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
      "{ 'class': 'SimpleStrategy', 'replication_factor': 1 } "
    );
  }

  template <> template <>
  void casst::create_keyspace_group::test<3>() /* and_durable_writes */
  {
    expect_equal
    (
      casst::create::keyspace("cmb_tables").
        with_replication<casst::create::simple_strategy>
        (
          casst::create::replication_factor(1)
        ).
        and_durable_writes(false).
        to_string(),

      "CREATE KEYSPACE cmb_tables WITH REPLICATION = "
      "{ 'class': 'SimpleStrategy', 'replication_factor': 1 } "
      "AND DURABLE_WRITES = false "
    );
  }

  template <> template <>
  void casst::create_keyspace_group::test<4>() /* and_durable_writes if_not_exists */
  {
    expect_equal
    (
      casst::create::keyspace<casst::create::if_not_exists>("cmb_tables").
        with_replication<casst::create::simple_strategy>
        (
          casst::create::replication_factor(1)
        ).
        and_durable_writes(false).
        to_string(),

      "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
      "{ 'class': 'SimpleStrategy', 'replication_factor': 1 } "
      "AND DURABLE_WRITES = false "
    );
  }

  template <> template <>
  void casst::create_keyspace_group::test<5>() /* network topology */
  {
    expect_equal
    (
      casst::create::keyspace<casst::create::if_not_exists>("cmb_tables").
        with_replication_network_topology(casst::create::data_center("dc1", 1)).
        to_string(),

      "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
      "{ 'class': 'NetworkTopologyStrategy', 'dc1': 1 } "
    );
  }

  template <> template <>
  void casst::create_keyspace_group::test<6>() /* network topology + data centers */
  {
    expect_equal
    (
      casst::create::keyspace<casst::create::if_not_exists>("cmb_tables").
        with_replication_network_topology
        (
          casst::create::data_center("dc1", 1),
          casst::create::data_center("dc2", 2),
          casst::create::data_center("dc3", 3),
          casst::create::data_center("dc4", 4),
          casst::create::data_center("dc5", 5)
        ).to_string(),

      "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
      "{ 'class': 'NetworkTopologyStrategy', "
      "'dc1': 1, "
      "'dc2': 2, "
      "'dc3': 3, "
      "'dc4': 4, "
      "'dc5': 5 "
      "} "
    );
  }
}
