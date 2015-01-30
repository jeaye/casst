#pragma once

#include <jest/jest.hpp>

#include <casst/update/update.hpp>
#include <casst/compare.hpp>
#include <casst/arithmetic.hpp>
#include <casst/row.hpp>
#include <casst/json/map.hpp>
#include <casst/json/set.hpp>
#include <casst/json/list.hpp>

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
    expect_equal
    (
      casst::update("foo").set(casst::equal("alive", true)).to_string(),

      "UPDATE foo SET alive = true  "
    );
    expect_equal
    (
      casst::update("foo").using_(casst::option::ttl(0)).
        set
        (
          casst::equal("foo", casst::sum("foo", 2)),
          casst::equal("bar", "spam")
        ).
        to_string(),

      "UPDATE foo USING TTL 0 SET foo = foo + 2, bar = 'spam'  "
    );
  }

  template <> template <>
  void casst::update_group::test<3>() /* where */
  {
    expect_equal
    (
      casst::update("foo").
        set(casst::equal("alive", true)).
        where(casst::equal("alive", false)).
        to_string(),

      "UPDATE foo SET alive = true WHERE alive = false "
    );
    expect_equal
    (
      casst::update("foo").
        set(casst::equal("alive", true)).
        where
        (
          casst::equal("alive", false),
          casst::and_(),
          casst::not_equal("name", "simba")
        ).
        to_string(),

     "UPDATE foo SET alive = true WHERE alive = false AND name <> 'simba' "
    );
  }

  template <> template <>
  void casst::update_group::test<4>() /* in */
  {
    expect_equal
    (
      casst::update("foo").
        set(casst::equal("alive", true)).
        where(casst::row("name").in("user1", "user2")).
        to_string(),

     "UPDATE foo SET alive = true WHERE name IN ( 'user1', 'user2' ) "
    );
    expect_equal
    (
      casst::update("foo").
        set(casst::equal("value", casst::null())).
        where(casst::row("age").in(42, 37, 10)).
        to_string(),

     "UPDATE foo SET value = null WHERE age IN ( 42, 37, 10 ) "
    );
  }

  template <> template <>
  void casst::update_group::test<5>() /* if */
  {
    expect_equal
    (
      casst::update("foo").
        set(casst::equal("alive", true)).
        if_(casst::equal("alive", false)).
        to_string(),

     "UPDATE foo SET alive = true IF alive = false "
    );
    expect_equal
    (
      casst::update("foo").
        set(casst::equal("alive", true)).
        if_
        (
          casst::and_
          (
            casst::equal("alive", false),
            casst::not_equal("name", "simba"),
            casst::greater("strength", 180)
          )
        ).
        to_string(),

      "UPDATE foo SET alive = true IF alive = false AND name <> 'simba' "
      "AND strength > 180 "
    );
  }

  template <> template <>
  void casst::update_group::test<6>() /* map */
  {
    expect_equal
    (
      casst::update("foo").
        set(casst::equal
        (
          "inventory",
          casst::json::map
          {
            { "weapon", "luck" },
            { "coins", 0 },
          }
        )).
        if_(casst::equal("alive", true)).
        to_string(),

     "UPDATE foo SET inventory = { 'coins': 0, 'weapon': 'luck' } "
     "IF alive = true "
    );
  }

  template <> template <>
  void casst::update_group::test<7>() /* set */
  {
    expect_equal
    (
      casst::update("foo").
        set(casst::equal
        (
          "weapons",
          casst::json::set
          {
            "good looks",
            "rail gun",
          }
        )).
        if_(casst::equal("alive", true)).
        to_string(),

     "UPDATE foo SET weapons = { 'good looks', 'rail gun' } "
     "IF alive = true "
    );
  }

  template <> template <>
  void casst::update_group::test<8>() /* list */
  {
    expect_equal
    (
      casst::update("foo").
        set(casst::equal
        (
          "weapons",
          casst::json::list
          {
            "good looks",
            "rail gun",
          }
        )).
        if_(casst::equal("alive", true)).
        to_string(),

     "UPDATE foo SET weapons = [ 'good looks', 'rail gun' ] "
     "IF alive = true "
    );
  }

  template <> template <>
  void casst::update_group::test<9>() /* collection subtraction */
  {
    expect_equal
    (
      casst::update("users").set
      (
        casst::equal
        (
          "emails",
          casst::diff("emails", casst::json::set{ "fb@friendsofmordor.org" })
        )
      ).where(casst::equal("user_id", "frodo")).to_string(),

      "UPDATE users SET emails = emails - { 'fb@friendsofmordor.org' } "
      "WHERE user_id = 'frodo' "
    );
  }

  template <> template <>
  void casst::update_group::test<10>() /* collection addition */
  {
    expect_equal
    (
      casst::update("users").set
      (
        casst::equal
        (
          "emails",
          casst::sum
          (
            casst::json::list{ "fb@friendsofmordor.org" },
            casst::column("emails")
          )
        )
      ).where(casst::equal("user_id", "frodo")).to_string(),

      "UPDATE users SET emails = [ 'fb@friendsofmordor.org' ] + emails "
      "WHERE user_id = 'frodo' "
    );
  }
}
