#pragma once

#include <jest/jest.hpp>

#include <casst/select/select.hpp>
#include <casst/compare.hpp>

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
    expect_equal
    (
      casst::select("foo").from("kitty").to_string(),

      "SELECT foo FROM kitty "
    );
    expect_equal
    (
      casst::select("foo", "bar").from("kitty").to_string(),

      "SELECT foo, bar FROM kitty "
    );
  }

  template <> template <>
  void casst::select_group::test<1>() /* distinct */
  {
    expect_equal
    (
      casst::select_distinct("foo").from("kitty").to_string(),

      "SELECT DISTINCT foo FROM kitty "
    );
    expect_equal
    (
      casst::select_distinct("foo", "bar").from("kitty").to_string(),

      "SELECT DISTINCT foo, bar FROM kitty "
    );
  }

  template <> template <>
  void casst::select_group::test<2>() /* count */
  {
    expect_equal
    (
      casst::select_count("foo").from("kitty").to_string(),

      "SELECT COUNT ( * ) foo FROM kitty "
    );
    expect_equal
    (
      casst::select_count("foo", "bar").from("kitty").to_string(),

      "SELECT COUNT ( * ) foo, bar FROM kitty "
    );
  }

  template <> template <>
  void casst::select_group::test<3>() /* expressions */
  {
    expect_equal
    (
      casst::select(casst::alias("foo", "f")).from("kitty").to_string(),

      "SELECT foo AS f FROM kitty "
    );
    expect_equal
    (
      casst::select(casst::alias("foo", "f"),
        casst::alias("bar", "b")).from("kitty").to_string(),

      "SELECT foo AS f, bar AS b FROM kitty "
    );

    expect_equal
    (
      casst::select(casst::alias(casst::writetime("foo"), "f")).
        from("kitty").
        to_string(),

      "SELECT WRITETIME( foo ) AS f FROM kitty "
    );

    expect_equal
    (
      casst::select(casst::alias(casst::ttl("foo"), "f")).
        from("kitty").
        to_string(),

      "SELECT TTL( foo ) AS f FROM kitty "
    );
  }

  template <> template <>
  void casst::select_group::test<4>() /* basic where */
  {
    expect_equal
    (
      casst::select_count("foo").from("kitty").
        where(casst::equal("name", "meow")).
        to_string(),

      "SELECT COUNT ( * ) foo FROM kitty WHERE name = 'meow' "
    );
    expect_equal
    (
      casst::select_count("foo", "bar").from("kitty").
      where(casst::equal("age", 42)).
      to_string(),

      "SELECT COUNT ( * ) foo, bar FROM kitty WHERE age = 42 "
    );
    expect_equal
    (
      casst::select_count("foo", "bar").from("kitty").
        where(casst::equal("blah", casst::binding())).
        to_string(),

      "SELECT COUNT ( * ) foo, bar FROM kitty WHERE blah = ? "
    );
  }

  template <> template <>
  void casst::select_group::test<5>() /* where + and */
  {
    expect_equal
    (
      casst::select_count("foo").from("kitty").
        where
        (
          casst::equal("name", "meow"),
          casst::and_(),
          casst::less_equal("money", 30)
        ).to_string(),

      "SELECT COUNT ( * ) foo FROM kitty WHERE name = 'meow' "
      "AND money <= 30 "
    );
    expect_equal
    (
      casst::select_count("foo", "bar").from("kitty").
        where
        (
          casst::equal("age", 42),
          casst::and_(),
          casst::not_equal("alive", false)
        ).to_string(),

      "SELECT COUNT ( * ) foo, bar FROM kitty WHERE age = 42 "
      "AND alive <> false "
    );
  }

  template <> template <>
  void casst::select_group::test<6>() /* where + row_slice */
  {
    expect_equal
    (
      casst::select_count("foo").from("kitty").
        where
        (
          casst::equal("name", "meow"),
          casst::and_(),
          casst::not_equal
          (
            casst::row_slice
            (
              casst::column("bat"),
              casst::column("sword")
            ),
            casst::row_slice("tab", "drows")
          )
        ).to_string(),

      "SELECT COUNT ( * ) foo FROM kitty WHERE name = 'meow' "
      "AND ( bat, sword ) <> ( 'tab', 'drows' ) "
    );
  }

  template <> template <>
  void casst::select_group::test<7>() /* limit */
  {
    expect_equal
    (
      casst::select_distinct("foo").from("kitty").
        limit(2).
        to_string(),

      "SELECT DISTINCT foo FROM kitty LIMIT 2 "
    );
  }

  template <> template <>
  void casst::select_group::test<8>() /* allow filtering */
  {
    expect_equal
    (
      casst::select_distinct("foo").from("kitty").
        limit(2).allow_filtering().
        to_string(),

      "SELECT DISTINCT foo FROM kitty LIMIT 2 ALLOW FILTERING "
    );
  }

  template <> template <>
  void casst::select_group::test<9>() /* token */
  {
    expect_equal
    (
      casst::select("foo").from("kitty").
        where
        (
         casst::equal
         (
           casst::token(casst::column("period")),
           casst::token("third_age")
         )
        ).to_string(),

      "SELECT foo FROM kitty "
      "WHERE TOKEN ( period ) = TOKEN ( 'third_age' ) "
    );
    expect_equal
    (
      casst::select("foo").from("kitty").
        where
        (
         casst::equal
         (
           casst::token(casst::column("period")),
           casst::token("third_age")
         ),
         casst::and_(),
         casst::not_equal
         (
           casst::token(casst::column("answer")),
           casst::token(42)
         )
        ).to_string(),

      "SELECT foo FROM kitty "
      "WHERE TOKEN ( period ) = TOKEN ( 'third_age' ) "
      "AND TOKEN ( answer ) <> TOKEN ( 42 ) "
    );
  }

  template <> template <>
  void casst::select_group::test<10>() /* contains */
  {
    expect_equal
    (
      casst::select("album", "tags").from("playlists").
        where(casst::contains("tags", "blues")).
        to_string(),

      "SELECT album, tags FROM playlists WHERE tags CONTAINS 'blues' "
    );

    expect_equal
    (
      casst::select(casst::all()).from("playlists").
        where(casst::contains_key("venue", "2014-09-22 22:00:00-0700")).
        to_string(),

      "SELECT * FROM playlists "
      "WHERE venue CONTAINS KEY '2014-09-22 22:00:00-0700' "
    );
  }

  template <> template <>
  void casst::select_group::test<11>() /* order by */
  {
    expect_equal
    (
      casst::select(casst::all()).from("playlists").
        where(casst::equal("id", "62c36092-82a1-3a00-93d1-46196ee77204")).
        order_by<casst::order_by::desc>("song_order").
        limit(10).
        to_string(),

      "SELECT * FROM playlists WHERE id = '62c36092-82a1-3a00-93d1-46196ee77204' "
      "ORDER BY song_order DESC LIMIT 10 "
    );

    expect_equal
    (
      casst::select(casst::all()).from("playlists").
        where(casst::equal("id", "62c36092-82a1-3a00-93d1-46196ee77204")).
        order_by<casst::order_by::asc>("song_order").
        limit(10).
        to_string(),

      "SELECT * FROM playlists WHERE id = '62c36092-82a1-3a00-93d1-46196ee77204' "
      "ORDER BY song_order ASC LIMIT 10 "
    );
  }
}
