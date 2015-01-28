#pragma once

#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

#include <casst/json/value.hpp>
#include <casst/detail/render.hpp>

namespace casst
{
  namespace json
  {
    namespace detail
    {
      template <typename Tag>
      char constexpr const* delim_begin();
      template <typename Tag>
      char constexpr const* delim_end();

      template <typename Tag>
      class array
      {
        public:
          array() = default;
          array(std::initializer_list<value> &&list)
          {
            std::transform(list.begin(), list.end(), std::back_inserter(data_),
                           [](auto const &v){ return casst::detail::to_rvalue(v); });
          }

          template <typename T>
          friend std::ostream& operator <<(std::ostream &os, array<T> const &m);

        private:
          std::vector<std::string> data_;
      };

      template <typename T>
      std::ostream& operator <<(std::ostream &os, array<T> const &m)
      {
        os << delim_begin<T>();

        for(auto const &v : m.data_)
        { os << v << ", "; }
        if(m.data_.size())
        { os.seekp(-2, std::ios_base::end); }

        return os << delim_end<T>();
      }
    }
  }
}
