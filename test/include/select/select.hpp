#pragma once

#include <jest/jest.hpp>

#include <casst/select/select.hpp>

namespace casst
{
  struct select_test{};
  using select_group = jest::group<select_test>;
  static select_group const select_obj{ "select" };
}

namespace jest
{
  template <> template <>
  void casst::select_group::test<0>() /* basic */
  {
    expect_equal(casst::select("foo").from("kitty").to_string(),
                 "SELECT foo FROM kitty ");
    expect_equal(casst::select("foo", "bar").from("kitty").to_string(),
                 "SELECT foo, bar FROM kitty ");
  }

  template <> template <>
  void casst::select_group::test<1>() /* distinct */
  {
    expect_equal(casst::select_distinct("foo").from("kitty").to_string(),
                 "SELECT DISTINCT foo FROM kitty ");
    expect_equal(casst::select_distinct("foo", "bar").from("kitty").to_string(),
                 "SELECT DISTINCT foo, bar FROM kitty ");
  }

  template <> template <>
  void casst::select_group::test<2>() /* count */
  {
    expect_equal(casst::select_count("foo").from("kitty").to_string(),
                 "SELECT COUNT ( * ) foo FROM kitty ");
    expect_equal(casst::select_count("foo", "bar").from("kitty").to_string(),
                 "SELECT COUNT ( * ) foo, bar FROM kitty ");
  }

  template <> template <>
  void casst::select_group::test<3>() /* expressions */
  {
    expect_equal(casst::select(casst::alias("foo", "f")).from("kitty").to_string(),
                 "SELECT foo AS f FROM kitty ");
    expect_equal(casst::select(casst::alias("foo", "f"),
                  casst::alias("bar", "b")).from("kitty").to_string(),
                 "SELECT foo AS f, bar AS b FROM kitty ");

    expect_equal(casst::select(casst::alias(casst::writetime("foo"), "f")).
                  from("kitty").to_string(),
                 "SELECT WRITETIME( foo ) AS f FROM kitty ");

    expect_equal(casst::select(casst::alias(casst::ttl("foo"), "f")).
                  from("kitty").to_string(),
                 "SELECT TTL( foo ) AS f FROM kitty ");
  }
}
