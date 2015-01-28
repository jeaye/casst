#pragma once

#include <casst/update/detail/update.hpp>
#include <casst/option.hpp>

namespace casst
{
  inline auto update(std::string const &tab)
  { return detail::update::update<detail::update::step::base>{ tab }; }
}
