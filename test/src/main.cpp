#include <jest/jest.hpp>

#include <casst/create/keyspace.hpp>

/*
  CREATE INDEX
  CREATE KEYSPACE
  CREATE TABLE
  CREATE TRIGGER
  CREATE TYPE
  CREATE USER
*/

int main()
{
  using namespace casst;
  std::cout <<
    casst::create::keyspace<casst::create::if_not_exists>("cmb_tables").
      with_replication<casst::create::simple_strategy>(casst::create::replication_factor(1)).
        and_durable_writes(false).to_string();

  std::cout << std::endl;

  std::cout <<
    create::keyspace<create::if_not_exists>("cmb_tables").
      with_replication<create::simple_strategy>(create::replication_factor(1)).
        and_durable_writes(false).to_string();

  std::cout << std::endl;
}
