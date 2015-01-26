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
}
