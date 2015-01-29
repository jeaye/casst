#pragma once

#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

#include <casst/json/value.hpp>

namespace casst
{
  namespace json
  {
    class map
    {
      public:
        using value_type = std::pair<std::string const, value>;

        map() = default;
        map(std::initializer_list<value_type> &&list)
        { std::copy(list.begin(), list.end(), std::inserter(map_, map_.end())); }

        auto begin()
        { return map_.begin(); }
        auto begin() const
        { return map_.begin(); }
        auto end()
        { return map_.end(); }
        auto end() const
        { return map_.end(); }

        void push_back(value_type const &p)
        { map_.emplace(p); }

        friend std::ostream& operator <<(std::ostream &os, map const &m)
        {
          os << "{ ";

          for(auto const &v : m.map_)
          { os << "\'" << v.first << "\': " << v.second.data << ", "; }
          if(m.map_.size())
          { os.seekp(-2, std::ios_base::end); }

          return os << " }";
        }

      private:
        std::map<std::string, value> map_;
    };
  }
}
