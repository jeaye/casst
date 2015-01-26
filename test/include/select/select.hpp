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
    expect_equal(casst::select("foo").to_string(),
                 "SELECT foo  ");
    expect_equal(casst::select("foo", "bar").to_string(),
                 "SELECT foo, bar  ");
  }

  template <> template <>
  void casst::select_group::test<1>() /* distinct */
  {
    expect_equal(casst::select_distinct("foo").to_string(),
                 "SELECT DISTINCT foo  ");
    expect_equal(casst::select_distinct("foo", "bar").to_string(),
                 "SELECT DISTINCT foo, bar  ");
  }

  template <> template <>
  void casst::select_group::test<2>() /* count */
  {
    expect_equal(casst::select_count("foo").to_string(),
                 "SELECT COUNT ( * ) foo  ");
    expect_equal(casst::select_count("foo", "bar").to_string(),
                 "SELECT COUNT ( * ) foo, bar  ");
  }

  template <> template <>
  void casst::select_group::test<3>() /* expressions */
  {
    expect_equal(casst::select(casst::alias("foo", "f")).to_string(),
                 "SELECT foo AS f  ");
    expect_equal(casst::select(casst::alias("foo", "f"),
                  casst::alias("bar", "b")).to_string(),
                 "SELECT foo AS f, bar AS b  ");

    expect_equal(casst::select(casst::alias(casst::writetime("foo"), "f")).
                  to_string(),
                 "SELECT WRITETIME( foo ) AS f  ");

    expect_equal(casst::select(casst::alias(casst::ttl("foo"), "f")).
                  to_string(),
                 "SELECT TTL( foo ) AS f  ");
  }
}
