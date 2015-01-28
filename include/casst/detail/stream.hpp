#pragma once

#include <sstream>
#include <memory>

namespace casst
{
  namespace detail
  {
    /* XXX: GCC 4.9.x doesn't support movable streams, so we need to wrap
     * our commonly-used stream in a unique_ptr to make it movable.
     * This should be removed after GCC 5.0. */
    struct ostringstream
    {
      ostringstream()
        : stream{ std::make_unique<std::ostringstream>() }
      { }
      ostringstream(ostringstream &&) = default;
      ostringstream& operator =(ostringstream &&) = default;

      template <typename Diff, typename Dir>
      auto& seekp(Diff const diff, Dir const dir)
      { return stream->seekp(diff, dir); }

      std::string str() const
      { return stream->str(); }

      std::unique_ptr<std::ostringstream> stream;
    };

    template <typename T>
    auto& operator <<(ostringstream &oss, T const &t)
    { return (*oss.stream) << t; }
  }
}
