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
    std::string const str{ casst::create::keyspace("cmb_tables").
      with_replication_simple(casst::create::replication_factor(1)).to_string() };

    expect_equal(str, "CREATE KEYSPACE cmb_tables WITH REPLICATION = "
                      "{'class':'SimpleStrategy','replication_factor':1}");
  }
  
  template <> template <>
  void casst::create_keyspace_group::test<2>() /* with_replication if_not_exists */
  {
    std::string const str{ casst::create::keyspace_if_not_exists("cmb_tables").
      with_replication_simple(casst::create::replication_factor(1)).to_string() };

    expect_equal(str, "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
                      "{'class':'SimpleStrategy','replication_factor':1}");
  }

  template <> template <>
  void casst::create_keyspace_group::test<3>() /* and_durable_writes */
  {
    std::string const str{ casst::create::keyspace("cmb_tables").
      with_replication<casst::create::simple_strategy>(casst::create::replication_factor(1)).
      and_durable_writes(false).to_string() };

    expect_equal(str, "CREATE KEYSPACE cmb_tables WITH REPLICATION = "
                      "{'class':'SimpleStrategy','replication_factor':1} AND DURABLE_WRITES = false");
  }

  template <> template <>
  void casst::create_keyspace_group::test<4>() /* and_durable_writes if_not_exists */
  {
    std::string const str{ casst::create::keyspace<casst::create::if_not_exists>("cmb_tables").
      with_replication<casst::create::simple_strategy>(casst::create::replication_factor(1)).
      and_durable_writes(false).to_string() };

    expect_equal(str, "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
                      "{'class':'SimpleStrategy','replication_factor':1} AND DURABLE_WRITES = false");
  }

  template <> template <>
  void casst::create_keyspace_group::test<5>() /* network topology */
  {
    std::string const str{ casst::create::keyspace<casst::create::if_not_exists>("cmb_tables").
      with_replication_network_topology(casst::create::data_center("dc1", 1)).to_string() };

    expect_equal(str, "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
                      "{'class':'NetworkTopologyStrategy','db1':1}");
  }

  template <> template <>
  void casst::create_keyspace_group::test<6>() /* network topology more data centers */
  {
    std::string const str{ casst::create::keyspace<casst::create::if_not_exists>("cmb_tables").
      with_replication_network_topology(
          casst::create::data_center("dc1", 1),
          casst::create::data_center("dc2", 2),
          casst::create::data_center("dc3", 3),
          casst::create::data_center("dc4", 4),
          casst::create::data_center("dc5", 5)
      ).to_string() };

    expect_equal(str, "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
                      "{'class':'NetworkTopologyStrategy',"
                      "'db1':1,"
                      "'db2':2,"
                      "'db3':3,"
                      "'db4':4,"
                      "'db5':5"
                      "}");
  }
}
