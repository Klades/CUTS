#include "boost/test/unit_test.hpp"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

#include "cuts/Endpoint_Data.h"



struct fixture
{
  ACE_Time_Value tv;
  fixture (void)
    : endpoint_data_ (tv, 0)
  {
  }

  CUTS_Endpoint_Data endpoint_data_;
};

void constructor (void)
{
  CUTS_Endpoint_Data endpoint_data;

  ACE_Time_Value tv = endpoint_data.time_of_completion();
  size_t ds = endpoint_data.data_size();

  BOOST_CHECK (tv == ACE_Time_Value::zero);
  BOOST_CHECK (ds == 0);
}

void init_constructor(void)
{
 ACE_Time_Value ftv;
 CUTS_Endpoint_Data endpoint_data(ftv, 0);
 ACE_Time_Value tv = endpoint_data.time_of_completion();
 size_t ds = endpoint_data.data_size();

 BOOST_CHECK (tv == ACE_Time_Value::zero);
 BOOST_CHECK (ds == 0);
}

void copy_constructor (void)
{
  fixture f;
  CUTS_Endpoint_Data endpoint_data(f.endpoint_data_);

  ACE_Time_Value tv = endpoint_data.time_of_completion();
  size_t ds = endpoint_data.data_size();

  ACE_Time_Value ftv = f.endpoint_data_.time_of_completion();
  size_t fds = f.endpoint_data_.data_size();

  BOOST_CHECK (tv == ftv);
  BOOST_CHECK (ds == fds);
}


void operator_equal (void)
{
  fixture f;
  CUTS_Endpoint_Data endpoint_data;

  endpoint_data = f.endpoint_data_;

  ACE_Time_Value tv = endpoint_data.time_of_completion();
  size_t ds = endpoint_data.data_size();

  ACE_Time_Value ftv = f.endpoint_data_.time_of_completion();
  size_t fds = f.endpoint_data_.data_size();

  BOOST_CHECK (tv == ftv);
  BOOST_CHECK (ds == fds);
}

void operator_graterthan(void)
{
 fixture f;
 CUTS_Endpoint_Data endpoint_data;
 ACE_Time_Value tv = endpoint_data.time_of_completion();
 ACE_Time_Value ftv = f.endpoint_data_.time_of_completion();
 
 if(endpoint_data > f.endpoint_data_)
 {
  BOOST_CHECK(tv > ftv);
 }
 else
 {
  BOOST_CHECK(tv <= ftv);	
 }
}

void operator_graterthanorequal(void)
{
  fixture f;
  CUTS_Endpoint_Data endpoint_data;
  ACE_Time_Value tv = endpoint_data.time_of_completion();
  ACE_Time_Value ftv = f.endpoint_data_.time_of_completion();
 
  if(endpoint_data >= f.endpoint_data_)
  {
   BOOST_CHECK(tv >= ftv);
  }
  else
  {
   BOOST_CHECK(tv < ftv);	
  }
}


void operator_lessthan(void)
{
  fixture f;
  CUTS_Endpoint_Data endpoint_data;
  ACE_Time_Value tv = endpoint_data.time_of_completion();
  ACE_Time_Value ftv = f.endpoint_data_.time_of_completion();
 
  if(endpoint_data < f.endpoint_data_)
  {
   BOOST_CHECK(tv < ftv);
  }
  else
  {
   BOOST_CHECK(tv >= ftv);	
  }

}

void operator_lessthanorequal(void)
{
  fixture f;
  CUTS_Endpoint_Data endpoint_data;
  ACE_Time_Value tv = endpoint_data.time_of_completion();
  ACE_Time_Value ftv = f.endpoint_data_.time_of_completion();
 
  if(endpoint_data <= f.endpoint_data_)
  {
   BOOST_CHECK(tv <= ftv);
  }
  else
  {
   BOOST_CHECK(tv > ftv);	
  }
}



void operator_doubleequal(void)
{
  fixture f;
  CUTS_Endpoint_Data endpoint_data;
  ACE_Time_Value tv = endpoint_data.time_of_completion();
  ACE_Time_Value ftv = f.endpoint_data_.time_of_completion();
 
  if(endpoint_data == f.endpoint_data_)
  {
   BOOST_CHECK(tv == ftv);
  }
  else
  {
   BOOST_CHECK(tv != ftv);	
  }
}

void operator_increment(void)
{
  fixture f;
  CUTS_Endpoint_Data endpoint_data;
  ACE_Time_Value tv = endpoint_data.time_of_completion();
  ACE_Time_Value ftv = f.endpoint_data_.time_of_completion();
  size_t ds = endpoint_data.data_size();
  size_t fds = f.endpoint_data_.data_size();
 
  endpoint_data += f.endpoint_data_;
 
  BOOST_CHECK(tv == (tv + ftv));
  BOOST_CHECK(fds == (ds + fds));
}


boost::unit_test::test_suite *
init_unit_test_suite (int argc, char * argv[])
{
  using namespace ::boost::unit_test;

  test_suite * test = BOOST_TEST_SUITE ("CUTS_Endpoint_Data");

  // Add the unit test to the master suite.
  test->p_name.value = "CUTS_Endpoint_Data";
  test->add (make_test_case (&constructor, "CUTS_Endpoint_Data(void)"));
  test->add (make_test_case (&init_constructor, "CUTS_Endpoint_Data (const ACE_Time_Value & toc;, size_t datasize;)"));
  test->add (make_test_case (&copy_constructor, "CUTS_Endpoint_Data (const CUTS_Endpoint_Data & src;)"));
  test->add (make_test_case (&operator_equal, "CUTS_Endpoint_Data & operator = (const CUTS_Endpoint_Data & rhs;)"));
  test->add (make_test_case (&operator_graterthan, "bool operator > (const CUTS_Endpoint_Data & rhs;)"));
  test->add (make_test_case (&operator_graterthanorequal, "bool operator >= (const CUTS_Endpoint_Data & rhs;)"));
  test->add (make_test_case (&operator_lessthan, "bool operator > (const CUTS_Endpoint_Data & rhs;)"));
  test->add (make_test_case (&operator_lessthanorequal, "bool operator <= (const CUTS_Endpoint_Data & rhs;)"));
  test->add (make_test_case (&operator_doubleequal, "bool operator == (const CUTS_Endpoint_Data & rhs;)"));
  test->add (make_test_case (&operator_increment, "const CUTS_Endpoint_Data & operator += (const CUTS_Endpoint_Data & rhs;)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);

  return test;
}

