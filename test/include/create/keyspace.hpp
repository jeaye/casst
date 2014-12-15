#pragma once

#include <jest/jest.hpp>

#include <casst/create/keyspace.hpp>

namespace casst
{
  struct back_insert_test{};
  using back_insert_group = jest::group<back_insert_test>;
  static back_insert_group const back_insert_obj{ "back_insert" };
}

namespace jest
{
  template <> template <>
  void casst::back_insert_group::test<0>() /* base */
  {
    casst::create::keyspace<casst::create::if_not_exists>("cmb_tables");
    casst::create::keyspace("cmb_tables");
    casst::create::keyspace_if_not_exists("cmb_tables");
  }
  
  template <> template <>
  void casst::back_insert_group::test<1>() /* with_replication */
  {
    std::string const str{ casst::create::keyspace_if_not_exists("cmb_tables").
      with_replication_simple(casst::create::replication_factor(1)).to_string() };

    expect_equal(str, "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
                      "{'class':'SimpleStrategy','replication_factor':1}");
  }

  template <> template <>
  void casst::back_insert_group::test<2>() /* and_durable_writes */
  {
    std::string const str{ casst::create::keyspace<casst::create::if_not_exists>("cmb_tables").
      with_replication<casst::create::simple_strategy>(casst::create::replication_factor(1)).
      and_durable_writes(false).to_string() };

    expect_equal(str, "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
                      "{'class':'SimpleStrategy','replication_factor':1} AND DURABLE_WRITES = false");
  }

  template <> template <>
  void casst::back_insert_group::test<3>() /* network topology */
  {
    std::string const str{ casst::create::keyspace<casst::create::if_not_exists>("cmb_tables").
      with_replication_network_topology(casst::create::data_center("dc1", 1)).to_string() };

    expect_equal(str, "CREATE KEYSPACE IF NOT EXISTS cmb_tables WITH REPLICATION = "
                      "{'class':'NetworkTopologyStrategy','db1':1}");
  }

  template <> template <>
  void casst::back_insert_group::test<4>() /* network topology more data centers */
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
