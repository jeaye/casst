#pragma once

#include <jest/jest.hpp>

#include <casst/delete/delete.hpp>

namespace casst
{
  struct delete_test{};
  using delete_group = jest::group<delete_test>;
  static delete_group const delete_obj{ "delete" };
}

namespace jest
{
  template <> template <>
  void casst::delete_group::test<0>() /* cols */
  {
    expect_equal(casst::delete_().from("turb").to_string(),
                 "DELETE FROM turb ");
    expect_equal(casst::delete_().cols().from("turb").to_string(),
                 "DELETE FROM turb ");
    expect_equal(casst::delete_().cols("col1", "col2", "col3").from("turb").to_string(),
                 "DELETE col1, col2, col3 FROM turb ");
  }

  template <> template <>
  void casst::delete_group::test<1>() /* where */
  {
    expect_equal(casst::delete_().from("turb").
                                  where(casst::equal("alive", false)).to_string(),
                 "DELETE FROM turb WHERE alive = false ");
    expect_equal(casst::delete_().cols("col1", "col2", "col3").from("turb").
                                  where(casst::equal("age", 18)).to_string(),
                 "DELETE col1, col2, col3 FROM turb WHERE age = 18 ");
    expect_equal(casst::delete_().cols("col1", "col2", "col3").from("turb").
                                  where(casst::equal("name", "meow")).to_string(),
                 "DELETE col1, col2, col3 FROM turb WHERE name = 'meow' ");
    expect_equal(casst::delete_().from("turb").
                                  where(casst::row("meow").in("kitty", "cat")).to_string(),
                 "DELETE FROM turb WHERE meow IN ( 'kitty', 'cat' ) ");
  }

  template <> template <>
  void casst::delete_group::test<2>() /* where + and */
  {
    expect_equal(casst::delete_().from("people").
                                  where(casst::row("meow").in("kitty", "cat")).
                                  if_
                                  (
                                    casst::equal("name", "meow"),
                                    casst::and_(),
                                    casst::equal("alive", false)
                                  ).to_string(),
                 "DELETE FROM people WHERE meow IN ( 'kitty', 'cat' ) IF name = 'meow' AND alive = false ");
  }

  template <> template <>
  void casst::delete_group::test<3>() /* timestamp */
  {
    expect_equal(casst::delete_().from("people").using_timestamp(476500).
                                  where(casst::equal("alive", false)).to_string(),
                 "DELETE FROM people USING TIMESTAMP 476500 WHERE alive = false ");
    expect_equal(casst::delete_().from("people").using_timestamp(0).
                                  where(casst::equal("alive", false)).to_string(),
                 "DELETE FROM people USING TIMESTAMP 0 WHERE alive = false ");
  }

  template <> template <>
  void casst::delete_group::test<4>() /* exists */
  {
    expect_equal(casst::delete_().from("turb").if_exists().to_string(),
                 "DELETE FROM turb IF EXISTS ");
    expect_equal(casst::delete_().cols().from("turb").if_exists().to_string(),
                 "DELETE FROM turb IF EXISTS ");
    expect_equal(casst::delete_().cols("col1", "col2", "col3").from("turb").if_exists().to_string(),
                 "DELETE col1, col2, col3 FROM turb IF EXISTS ");
  }
}
