#pragma once

#include <jest/jest.hpp>

#include <casst/update/update.hpp>
#include <casst/compare.hpp>
#include <casst/arithmetic.hpp>

namespace casst
{
  struct update_test{};
  using update_group = jest::group<update_test>;
  static update_group const update_obj{ "update" };
}

namespace jest
{
  template <> template <>
  void casst::update_group::test<0>() /* basic */
  {
    expect_equal(casst::update("foo").to_string(), "UPDATE foo ");
    expect_equal(casst::update("space.foo").to_string(), "UPDATE space.foo ");
  }

  template <> template <>
  void casst::update_group::test<1>() /* using */
  {
    expect_equal(casst::update("foo").using_(casst::option::ttl(0)).to_string(),
                 "UPDATE foo USING TTL 0 ");
    expect_equal(casst::update("foo").using_
                                      (
                                        casst::option::ttl(42),
                                        casst::and_(),
                                        casst::option::timestamp(77)
                                      ).to_string(),
                 "UPDATE foo USING TTL 42 AND TIMESTAMP 77 ");
  }

  template <> template <>
  void casst::update_group::test<2>() /* set */
  {
    expect_equal(casst::update("foo").
                  using_(casst::option::ttl(0)).
                  set
                  (
                    casst::equal("foo", casst::sum("foo", 2)),
                    casst::equal("bar", "spam")
                  ).
                  to_string(),
                 "UPDATE foo USING TTL 0 SET foo = foo + 2, bar = 'spam'  ");
  }
}
