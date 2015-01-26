#pragma once

#include <string>
#include <sstream>

#include <casst/column.hpp>

namespace casst
{
  namespace detail
  {
    template <typename T>
    struct lvalue_renderer
    { T const &data; };
    template <typename T>
    struct rvalue_renderer
    { T const &data; };
    
    template <typename T>
    auto render_lvalue(T const &t)
    { return lvalue_renderer<T>{ t }; }
    template <typename T>
    auto render_rvalue(T const &t)
    { return rvalue_renderer<T>{ t }; }

    template <typename T>
    std::ostream& operator <<(std::ostream &os, lvalue_renderer<T> const &t)
    { return os << t.data; }

    template <typename T>
    std::ostream& operator <<(std::ostream &os, rvalue_renderer<T> const &t)
    { return os << t.data; }
    template <>
    inline std::ostream& operator <<<std::string>(std::ostream &os,
                                            rvalue_renderer<std::string> const &str)
    { return os << "'" << str.data << "'"; }

    /* rvalues, in CQL, are quoted or literal values. */
    template <typename T>
    std::string to_rvalue(T const &t)
    { return std::to_string(t); }
    inline std::string to_rvalue(std::string const &str)
    { return "'" + str + "'"; }
    inline std::string to_rvalue(char const * const str)
    { return to_rvalue(std::string{ str }); }

    inline std::string to_rvalue(detail::column const &column)
    { return column.name_; }

    /* lvalues, in CQL, are unquoted names. */
    template <typename T>
    std::string to_lvalue(T const &t)
    { return std::to_string(t); }
    inline std::string to_lvalue(std::string const &str)
    { return str; }
    inline std::string to_lvalue(char const * const str)
    { return str; }

    inline std::string to_lvalue(detail::column const &column)
    { return column.name_; }
  }
}
