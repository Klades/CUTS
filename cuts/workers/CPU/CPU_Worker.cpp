// $Id$

#include "CPU_Worker.h"

#if !defined (__CUTS_INLINE__)
#include "CPU_Worker.inl"
#endif

CUTS_WORKER_FACTORY_EXPORT_IMPL (CUTS_CPU_Worker);

#include "cuts/utils/Property_Map.h"
#include "cuts/utils/Property_Map_File.h"
#include "boost/bind.hpp"
#include <algorithm>
#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// class CUTS_LD_CPU_Worker

//
// load_profile
//
int CUTS_LD_CPU_Worker::load_profile (const ACE_CString & profile)
{
  CUTS_Property_Map prop_map;
  CUTS_Property_Map_File file (prop_map);

  if (!file.read (profile.c_str ()))
    return -1;

  // We need to convert to values into integer format.
  size_t msec;

  CUTS_Property_Map::const_iterator iter (prop_map.map ());

  for ( ; !iter.done (); ++ iter)
  {
    std::istringstream istr (iter->item ().c_str ());
    istr >> msec;

    if (!istr.fail ())
    {
      switch (this->profile_.bind (iter->key (), msec))
      {
      case 1:
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - duplicate entry in profile [%s]\n",
                    iter->key ().c_str ()));
        break;

      case -1:
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to store profile entry [%s]\n",
                    iter->key ().c_str ()));
        break;
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to parse value for key=%s\n",
                  iter->key ().c_str ()));
    }

  }

  return 0;
}

//
// profile_run
//
int CUTS_LD_CPU_Worker::profile_run (const ACE_CString & key)
{
  map_type::VALUE msec;

  // This is case of optimize for the fast path design pattern. Since
  // we want to fast path to be when the key is found if profile, we
  // assume this is the most likely case to happen.
  if (this->profile_.find (key, msec) == 0)
  {
    CUTS_CPU_Worker::run (msec);
    return 0;
  }

  return -1;
}

//
// workload
//
double CUTS_LD_CPU_Worker::workload (const ACE_CString & key) const
{
  double workload = 0.0;

  if (this->profile_.find (key, workload) != 0)
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to find workload for %s\n",
                key.c_str ()));

  return workload;
}
