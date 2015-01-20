#pragma once

#include <string>
#include <iostream>

#include <casst/detail/render.hpp>

namespace casst
{
  namespace detail
  {
    using sigil = char const * (*)();

    char constexpr const* equal()
    { return " = "; }
    char constexpr const* not_equal()
    { return " <> "; }
    char constexpr const* less()
    { return " < "; }
    char constexpr const* less_equal()
    { return " <= "; }
    char constexpr const* greater()
    { return " > "; }
    char constexpr const* greater_equal()
    { return " >= "; }

    template <sigil Sigil, typename T>
    struct compare
    {
      std::string name;
      T value{};
    };

    template <sigil Sigil, typename T>
    std::ostream& operator <<(std::ostream &os, compare<Sigil, T> const &e)
    { return os << e.name << Sigil() << std::boolalpha << detail::render(e.value) << " "; }
  }

  template <typename T>
  auto equal(std::string const &name, T const &value)
  { return detail::compare<&detail::equal, T>{ name, value }; }
  auto equal(std::string const &name, char const * const value)
  { return detail::compare<&detail::equal, std::string>{ name, value }; }

  template <typename T>
  auto not_equal(std::string const &name, T const &value)
  { return detail::compare<&detail::not_equal, T>{ name, value }; }
  auto not_equal(std::string const &name, char const * const value)
  { return detail::compare<&detail::not_equal, std::string>{ name, value }; }

  template <typename T>
  auto less(std::string const &name, T const &value)
  { return detail::compare<&detail::less, T>{ name, value }; }
  auto less(std::string const &name, char const * const value)
  { return detail::compare<&detail::less, std::string>{ name, value }; }

  template <typename T>
  auto less_equal(std::string const &name, T const &value)
  { return detail::compare<&detail::less_equal, T>{ name, value }; }
  auto less_equal(std::string const &name, char const * const value)
  { return detail::compare<&detail::less_equal, std::string>{ name, value }; }

  template <typename T>
  auto greater(std::string const &name, T const &value)
  { return detail::compare<&detail::greater, T>{ name, value }; }
  auto greater(std::string const &name, char const * const value)
  { return detail::compare<&detail::greater, std::string>{ name, value }; }

  template <typename T>
  auto greater_equal(std::string const &name, T const &value)
  { return detail::compare<&detail::greater_equal, T>{ name, value }; }
  auto greater_equal(std::string const &name, char const * const value)
  { return detail::compare<&detail::greater_equal, std::string>{ name, value }; }
}
