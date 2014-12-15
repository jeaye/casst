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
                            columns(casst::text("name")).to_string() };
    expect_equal(str, "CREATE TABLE table ( name text ) ");
  }

  template <> template <>
  void casst::create_table_group::test<2>() /* types */
  {
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::ascii("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name ascii ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::text("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name text ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::varchar("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name varchar ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::blob("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name blob ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::inet("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name inet ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::list("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name list ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::map("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name map ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::set("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name set ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::tuple("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name tuple ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::counter("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name counter ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::timestamp("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name timestamp ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::timeuuid("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name timeuuid ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::uuid("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name uuid ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::bigint("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name bigint ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::boolean("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name boolean ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::decimal("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name decimal ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::_double("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name double ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::_float("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name float ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::_int("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name int ) ");
    }
    {
      std::string const str{ casst::create::table_if_not_exists("table").
                              columns(casst::varint("name")).to_string() };
      expect_equal(str, "CREATE TABLE table ( name varint ) ");
    }
  }
}
