// $Id$

#include "ace/Atomic_Op.h"
#include "ace/Condition_T.h"
#include "ace/High_Res_Timer.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/Task.h"
#include "ace/streams.h"
#include "cuts/workers/CPU/CPU_Worker.h"

/**
 * @struct CUTS_Thread_Config
 */
struct CUTS_Thread_Config
{
  CUTS_Thread_Config (void)
    : elapsed_ (ACE_Time_Value::zero)
  {

  }

  int cpu_;

  double msec_;

  ACE_Time_Value elapsed_;
};

/**
 * @class CPU_Thread_Test
 */
class CPU_Thread_Test : public ACE_Task_Base
{
public:
  typedef ACE_Array <CUTS_Thread_Config> config_t;

  CPU_Thread_Test (void)
    : ready_ (lock_)
  {

  }

  virtual int svc (void)
  {
    // Instantiate a new CPU worker.
    CUTS_CPU_Worker cpu;
    size_t index;

    do
    {
      // Increment the number of active threads
      ACE_GUARD_RETURN (ACE_RW_Thread_Mutex, guard, this->lock_, -1);
      index = this->active_ ++;

      // Notify the threads to begin execution.
      if (index == this->config_.size () - 1)
        this->ready_.broadcast ();
    } while (0);

    // Execute the CPU for the number of set msec.
    ACE_High_Res_Timer timer;

    timer.start ();
    cpu.run (this->config_[index].msec_);
    timer.stop ();

    // Get the elapsed time for the execution.
    timer.elapsed_time (this->config_[index].elapsed_);

    return 0;
  }

  int activate (void)
  {
    long flags = THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED;
    this->active_ = 0;

    return ACE_Task_Base::activate (flags, this->config_.size ());
  }

  config_t & config (void)
  {
    return this->config_;
  }

private:
  ACE_Array <CUTS_Thread_Config> config_;

  size_t active_;

  ACE_RW_Thread_Mutex lock_;

  ACE_Condition <ACE_RW_Thread_Mutex> ready_;
};

//
// operator >>
//
std::istream & operator >> (std::istream & in, CPU_Thread_Test & test)
{
  // Read the number of threads to configure.
  size_t count;
  in >> count;
  test.config ().size (count);

  // Read each of the thread configuration(s).
  for (size_t i = 0; i < count; ++ i)
    in >> test.config ()[i].cpu_ >> test.config ()[i].msec_;

  return in;
}

//
// main
//
int main (int argc, char * argv [])
{
  CPU_Thread_Test test;

  // Load the configuration for the test.
  std::ifstream fin;
  fin.open (argv[1]);

  if (!fin.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to open %s\n",
                       argv[1]),
                       1);

  // Read the number of threads to configure.
  fin >> test;
  fin.close ();

  // Activate the test threads.
  test.activate ();

  // Wait for all the threads to return.
  test.wait ();

  // Print the results to standard output.
  for (size_t i = 0; i < test.config ().size (); ++ i)
    std::cout << test.config ()[i].cpu_ << " "
              << test.config ()[i].msec_ << " "
              << test.config ()[i].elapsed_.msec () << std::endl;

  return 0;
}
