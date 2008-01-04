// $Id$

#include "boost/test/unit_test.hpp"

// function spec.
bool init_unit_test_suite (void);

//
// main
//
int main (int argc, char * argv [])
{
  return ::boost::unit_test::unit_test_main (&init_unit_test_suite, argc, argv);
}
