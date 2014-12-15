#pragma once

namespace casst
{
  namespace create
  {
    struct overwrite
    { static char constexpr const * const value{ "" }; };
    struct if_not_exists
    { static char constexpr const * const value{ "IF NOT EXISTS " }; };
  }
}
