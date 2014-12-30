#pragma once

#include <string>
#include <sstream>
#include <utility>

namespace casst
{
  using data_type_t = std::pair<std::string, std::string>;
  using data_func_t = data_type_t (*)(std::string const&);

  inline data_type_t ascii(std::string const &name)
  { return { name, "ascii" }; }
  inline data_type_t text(std::string const &name)
  { return { name, "text" }; }
  inline data_type_t varchar(std::string const &name)
  { return { name, "varchar" }; }

  inline data_type_t blob(std::string const &name)
  { return { name, "blob" }; }
  inline data_type_t inet(std::string const &name)
  { return { name, "inet" }; }

  template <data_func_t T>
  data_type_t list(std::string const &name)
  { return { name, "list< " + T(name).second + " >" }; }
  template <data_func_t K, data_func_t T>
  data_type_t map(std::string const &name)
  { return { name, "map< " + K(name).second + ", " + T(name).second + " >" }; }
  template <data_func_t T>
  data_type_t set(std::string const &name)
  { return { name, "set< " + T(name).second + " >" }; }
  template <data_func_t... Ts>
  data_type_t tuple(std::string const &name)
  {
    static_assert(sizeof...(Ts), "tuples cannot be zero-sized");

    std::ostringstream types;
    int const _[]{ (types << Ts(name).second << ", ", 0)... };
    static_cast<void>(_);
    types.seekp(-2, std::ios_base::end);
    types << " >";
    return { name, "tuple< " + types.str() };
  }
  template <data_func_t T>
  data_type_t frozen(std::string const &name)
  { return { name, "frozen< " + T(name).second + " >" }; }

  inline data_type_t counter(std::string const &name)
  { return { name, "counter" }; }
  inline data_type_t timestamp(std::string const &name)
  { return { name, "timestamp" }; }
  inline data_type_t timeuuid(std::string const &name)
  { return { name, "timeuuid" }; }
  inline data_type_t uuid(std::string const &name)
  { return { name, "uuid" }; }

  inline data_type_t bigint(std::string const &name)
  { return { name, "bigint" }; }
  inline data_type_t boolean(std::string const &name)
  { return { name, "boolean" }; }
  inline data_type_t decimal(std::string const &name)
  { return { name, "decimal" }; }
  inline data_type_t _double(std::string const &name)
  { return { name, "double" }; }
  inline data_type_t _float(std::string const &name)
  { return { name, "float" }; }
  inline data_type_t _int(std::string const &name)
  { return { name, "int" }; }
  inline data_type_t varint(std::string const &name)
  { return { name, "varint" }; }
}
