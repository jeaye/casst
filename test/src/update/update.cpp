#include <jest/jest.hpp>

#include "update/update.hpp"

int main()
{
  jest::worker const j{};
  return j();
}
