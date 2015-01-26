#include <jest/jest.hpp>

#include "select/select.hpp"

int main()
{
  jest::worker const j{};
  return j();
}
