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
    expect_equal
    (
      casst::create::table("table").
        columns(casst::text("name")).
        primary_key("name").
        to_string(),

      "CREATE TABLE table ( name text, PRIMARY KEY ( name ) )"
    );
  }

  template <> template <>
  void casst::create_table_group::test<2>() /* column if_not_exists */
  {
    expect_equal
    (
      casst::create::table_if_not_exists("table").
        columns(casst::text("name")).
        primary_key("name").
        to_string(),

      "CREATE TABLE IF NOT EXISTS table ( name text, PRIMARY KEY ( name ) )"
    );
  }

  template <> template <>
  void casst::create_table_group::test<3>() /* types */
  {
    auto const test([](auto const func)
    {
      auto const pair(func("name"));
      expect_equal
      (
        casst::create::table("table").
          columns(func("name")).
          primary_key("name").
          to_string(),

        "CREATE TABLE table ( name " + pair.second + ", "
        "PRIMARY KEY ( " + pair.first + " ) )"
      );
    });
    auto const test_if_not_exists([](auto const func)
    {
      auto const pair(func("name"));
      expect_equal
      (
        casst::create::table_if_not_exists("table").
          columns(func("name")).
          primary_key("name").
          to_string(),

        "CREATE TABLE IF NOT EXISTS table ( name " +
        pair.second + ", PRIMARY KEY ( " + pair.first + " ) )"
      );
    });

    test(&casst::ascii); test_if_not_exists(&casst::ascii);
    test(&casst::text); test_if_not_exists(&casst::text);
    test(&casst::varchar); test_if_not_exists(&casst::varchar);
    test(&casst::blob); test_if_not_exists(&casst::blob);
    test(&casst::inet); test_if_not_exists(&casst::inet);
    test(&casst::counter); test_if_not_exists(&casst::counter);
    test(&casst::timestamp); test_if_not_exists(&casst::timestamp);
    test(&casst::timeuuid); test_if_not_exists(&casst::timeuuid);
    test(&casst::uuid); test_if_not_exists(&casst::uuid);
    test(&casst::bigint); test_if_not_exists(&casst::bigint);
    test(&casst::boolean); test_if_not_exists(&casst::boolean);
    test(&casst::decimal); test_if_not_exists(&casst::decimal);
    test(&casst::_double); test_if_not_exists(&casst::_double);
    test(&casst::_float); test_if_not_exists(&casst::_float);
    test(&casst::_int); test_if_not_exists(&casst::_int);
    test(&casst::varint); test_if_not_exists(&casst::varint);
  }

  template <> template <>
  void casst::create_table_group::test<4>() /* generic types */
  {
    auto const test([](auto const func, std::string const &type)
    {
      auto const pair(func("name"));
      expect_equal
      (
        casst::create::table("table").
          columns(func("name")).
          primary_key("name").
          to_string(),

        "CREATE TABLE table ( name " + type + ", "
        "PRIMARY KEY ( " + pair.first + " ) )"
      );
    });
    auto const test_if_not_exists([](auto const func, std::string const &type)
    {
      auto const pair(func("name"));
      expect_equal
      (
        casst::create::table_if_not_exists("table").
          columns(func("name")).
          primary_key("name").
          to_string(),

        "CREATE TABLE IF NOT EXISTS table ( name " +
        type + ", PRIMARY KEY ( " + pair.first + " ) )"
      );
    });

    test(&casst::set<casst::text>, "set< text >");
    test_if_not_exists(&casst::set<casst::text>, "set< text >");
    test(&casst::set<casst::_int>, "set< int >");
    test_if_not_exists(&casst::set<casst::_int>, "set< int >");
    test(&casst::list<casst::text>, "list< text >");
    test_if_not_exists(&casst::list<casst::text>, "list< text >");
    test(&casst::list<casst::_float>, "list< float >");
    test_if_not_exists(&casst::list<casst::_float>, "list< float >");
    test(&casst::map<casst::text, casst::text>, "map< text, text >");
    test_if_not_exists(&casst::map<casst::text, casst::text>, "map< text, text >");
    test(&casst::map<casst::timeuuid, casst::bigint>, "map< timeuuid, bigint >");
    test_if_not_exists(&casst::map<casst::timeuuid, casst::bigint>,
                       "map< timeuuid, bigint >");

    test(&casst::tuple<casst::_float>, "tuple< float >");
    test_if_not_exists(&casst::tuple<casst::_float>, "tuple< float >");
    test(&casst::tuple<casst::_float, casst::blob, casst::set<casst::text>>,
         "tuple< float, blob, set< text > >");
    test_if_not_exists(&casst::tuple<casst::_float, casst::blob,
                                     casst::set<casst::text>>,
                       "tuple< float, blob, set< text > >");

    test(&casst::frozen<casst::text>, "frozen< text >");
    test_if_not_exists(&casst::frozen<casst::text>, "frozen< text >");
    test(&casst::frozen<casst::tuple<casst::inet>>, "frozen< tuple< inet > >");
    test_if_not_exists(&casst::frozen<casst::tuple<casst::inet>>,
                       "frozen< tuple< inet > >");
    test(&casst::frozen<casst::tuple<casst::blob, casst::inet>>,
         "frozen< tuple< blob, inet > >");
    test_if_not_exists(&casst::frozen<casst::tuple<casst::blob, casst::inet>>,
                       "frozen< tuple< blob, inet > >");
    test(&casst::frozen<casst::tuple<casst::varint, casst::blob, casst::inet>>,
         "frozen< tuple< varint, blob, inet > >");
    test_if_not_exists(&casst::frozen<casst::tuple<casst::varint,
                                                   casst::blob, casst::inet>>,
                       "frozen< tuple< varint, blob, inet > >");
    test(&casst::frozen<casst::tuple<casst::text, casst::tuple<casst::_int,
                                                               casst::uuid>>>,
         "frozen< tuple< text, tuple< int, uuid > > >");
    test_if_not_exists(&casst::frozen<casst::tuple<casst::text,
                                                   casst::tuple<casst::_int,
                                                                casst::uuid>>>,
                       "frozen< tuple< text, tuple< int, uuid > > >");
  }

  template <> template <>
  void casst::create_table_group::test<5>() /* composite */
  {
    expect_equal
    (
      casst::create::table("table").
        columns(casst::text("name")).
        primary_key(casst::create::composite("name", "age")).
        to_string(),

      "CREATE TABLE table ( name text, PRIMARY KEY ( ( name, age ) )"
    );
  }

  template <> template <>
  void casst::create_table_group::test<6>() /* composite if_not_exists */
  {
    expect_equal
    (
      casst::create::table_if_not_exists("table").
        columns(casst::text("name")).
        primary_key(casst::create::composite("name", "age")).
        to_string(),

      "CREATE TABLE IF NOT EXISTS table ( name text, PRIMARY KEY ( ( name, age ) )"
    );
  }

  template <> template <>
  void casst::create_table_group::test<7>() /* composite and more */
  {
    expect_equal
    (
      casst::create::table("table").
        columns(casst::text("name")).
        primary_key(casst::create::composite("name", "age"), "location").
        to_string(),

      "CREATE TABLE table ( name text, PRIMARY KEY ( ( name, age ), location ) )"
    );
  }

  template <> template <>
  void casst::create_table_group::test<8>() /* composite if_not_exists and more */
  {
    expect_equal
    (
      casst::create::table_if_not_exists("table").
        columns(casst::text("name")).
        primary_key(casst::create::composite("name", "age"), "location").
        to_string(),

      "CREATE TABLE IF NOT EXISTS table ( name text, "
      "PRIMARY KEY ( ( name, age ), location ) )"
    );
  }
}
