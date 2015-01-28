#include <jest/jest.hpp>

#include "insert/insert.hpp"

int main()
{
  jest::worker const j{};
  return j();
}
