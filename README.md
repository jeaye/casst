# casst - a C++14 CQL string builder

casst is a sane (header only) C++14 CQL string builder. Building complex queries using string concatenation is not only tedious, it's error-prone. By minimizing the number of magical literals, using the compiler to handle overload resolution and type checking, and providing a slew of static assertions that the CQL is correct, we can be more confident in the quality of our queries.

  * Header only (easy to add to any project)
  * Typesafe, C++14 interface
  * Absolutely no macros needed nor used
  * Extensive test suite (using [jest](https://github.com/jeaye/jest), a "sane and minimal C++14 unit test framework")

# examples
## select
```cpp
casst::select("album", "tags").from("playlists").
  where(casst::contains("tags", "blues")).
  to_string();

// yields: SELECT album, tags FROM playlists WHERE tags CONTAINS 'blues'
```
## update
```cpp
casst::update("foo").
  set(casst::equal("alive", true)).
  where(casst::row("name").in("user1", "user2")).
  to_string();

// yields: UPDATE foo SET alive = true WHERE name IN ( 'user1', 'user2' )
```
## delete
```cpp
casst::delete_().from("people").
  where(casst::row("meow").in("kitty", "cat")).
  if_
  (
    casst::equal
    (
      casst::row_slice
      (
        casst::column("name"),
        casst::column("age")
      ),
      casst::row_slice("meow", 18)
    )
  ).to_string();

// yields: 
// DELETE FROM people WHERE meow IN ( 'kitty', 'cat' )
// IF ( name, age ) = ( 'meow', 18 )
```

# documentation
There is quite a bit of documentation here on our [wiki](https://github.com/jeaye/casst/wiki). Beyond that, consider taking a look at the [tests](https://github.com/jeaye/casst/tree/master/test/include).

# license
casst is under the MIT open-source license.  
See the `LICENSE` file or http://opensource.org/licenses/MIT
