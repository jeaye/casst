#pragma once

#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

#include <casst/detail/render.hpp>

namespace casst
{
  namespace json
  {
    struct value
    {
      value() = delete;

      template <typename T>
      value(T const &t)
        : data{ detail::to_rvalue(t) }
      { }

      std::string data;
    };

    class map
    {
      public:
        using pair = std::pair<std::string const, value>;

        map() = default;
        map(std::initializer_list<pair> &&list)
        { std::copy(list.begin(), list.end(), std::inserter(map_, map_.end())); }

        friend std::ostream& operator <<(std::ostream &os, map const &m)
        {
          os << "{ ";
          for(auto const &v : m.map_)
          { os << "\'" << v.first << "\': " << v.second.data << ", "; }
          os.seekp(-2, std::ios_base::end);
          return os << " }";
        }

      private:
        std::map<std::string, value> map_;
    };
  }
}
