#pragma once

#include <jest/jest.hpp>

#include <casst/insert/insert.hpp>
#include <casst/option.hpp>
#include <casst/compare.hpp>
#include <casst/json/set.hpp>

namespace casst
{
  struct include_test{};
  using include_group = jest::group<include_test>;
  static include_group const include_obj{ "include" };
}

namespace jest
{
  template <> template <>
  void casst::include_group::test<0>() /* basic */
  {
    expect_equal
    (
      casst::insert("users", casst::columns("id", "todo")).
        values(42, "meet the president").
        to_string(),

      "INSERT INTO users ( id, todo ) VALUES ( 42, 'meet the president' ) "
    );
  }

  template <> template <>
  void casst::include_group::test<1>() /* if not exists */
  {
    expect_equal
    (
      casst::insert("users", casst::columns("id", "todo")).
        values(42, "meet the president").
        if_not_exists().
        to_string(),

      "INSERT INTO users ( id, todo ) VALUES ( 42, 'meet the president' ) "
      "IF NOT EXISTS "
    );
  }

  template <> template <>
  void casst::include_group::test<2>() /* using */
  {
    expect_equal
    (
      casst::insert("users", casst::columns("alive")).
        values(true).
        if_not_exists().
        using_
        (
          casst::option::ttl(42),
          casst::and_(),
          casst::option::timestamp(777)
        ).
        to_string(),

      "INSERT INTO users ( alive ) VALUES ( true ) "
      "IF NOT EXISTS USING TTL 42 AND TIMESTAMP 777 "
    );
  }

  template <> template <>
  void casst::include_group::test<3>() /* collections */
  {
    expect_equal
    (
      casst::insert("users", casst::columns("alive", "emails")).
        values
        (
          true,
          casst::json::set
          {
            "kitty@meow.com",
            "meowzer@catmail.org"
          }
        ).
        to_string(),

      "INSERT INTO users ( alive, emails ) VALUES ( true, "
      "{ 'kitty@meow.com', 'meowzer@catmail.org' } ) "
    );
  }
}
