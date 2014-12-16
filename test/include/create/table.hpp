#pragma once

#include <jest/jest.hpp>

#include <casst/create/table.hpp>

namespace casst
{
  struct create_table_test{};
  using create_table_group = jest::group<create_table_test>;
  static create_table_group const create_table_obj{ "create_table" };
}

namespace jest
{
  template <> template <>
  void casst::create_table_group::test<0>() /* base */
  {
    casst::create::table<casst::create::if_not_exists>("table");
    casst::create::table("table");
    casst::create::table_if_not_exists("table");
  }

  template <> template <>
  void casst::create_table_group::test<1>() /* column */
  {
    std::string const str{ casst::create::table_if_not_exists("table").
                            columns(casst::text("name")).
                              primary("name").to_string() };
    expect_equal(str, "CREATE TABLE table ( name text, PRIMARY KEY ( name ) )");
  }

  template <> template <>
  void casst::create_table_group::test<2>() /* types */
  {
    auto const test([](auto const func)
    {
      auto const pair(func("name"));
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(func("name")).
                                primary("name").to_string() };
      expect_equal(str, "CREATE TABLE table ( name " + pair.second + ", PRIMARY KEY ( " + pair.first + " ) )");
    });

    test(&casst::ascii);
    test(&casst::text);
    test(&casst::varchar);
    test(&casst::blob);
    test(&casst::inet);
    test(&casst::list);
    test(&casst::map);
    test(&casst::set);
    test(&casst::tuple);
    test(&casst::counter);
    test(&casst::timestamp);
    test(&casst::timeuuid);
    test(&casst::uuid);
    test(&casst::bigint);
    test(&casst::boolean);
    test(&casst::decimal);
    test(&casst::_double);
    test(&casst::_float);
    test(&casst::_int);
    test(&casst::varint);
  }

  template <> template <>
  void casst::create_table_group::test<3>() /* composite */
  {
    std::string const str{ casst::create::table_if_not_exists("table").
                            columns(casst::text("name")).
                              primary(casst::create::composite("name", "age")).to_string() };
    expect_equal(str, "CREATE TABLE table ( name text, PRIMARY KEY ( ( name, age ) )");
  }
}
