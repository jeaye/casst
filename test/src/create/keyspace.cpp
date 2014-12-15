#include <jest/jest.hpp>

#include "create/keyspace.hpp"

int main()
{
  jest::worker const j{};
  return j();
}
