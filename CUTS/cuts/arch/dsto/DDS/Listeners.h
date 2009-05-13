#ifndef LISTENERS_H
#define LISTENERS_H

#include "DSTO_ListenerBase.h"

namespace AppSpace
{
  class SubAppDDS;
}

namespace CUTS_DDS
{
  class DDS_Utility;
}

namespace DSTO_AppSpace_Impl
{
  // Generate one of these for each consumes port.
  class app_op_recv_Listener : public virtual ::CUTS_DDS::DSTO_ListenerBase
  {
  public:
    app_op_recv_Listener ( ::AppSpace::SubAppDDS * app,
                          ::CUTS_DDS::DDS_Utility & dds_utility);
    virtual ~app_op_recv_Listener (void);
    
    virtual void
    on_data_available (DataReader_ptr reader);

  private:
    ::AppSpace::SubAppDDS * app_;
    ::CUTS_DDS::DDS_Utility & dds_utility_;
  };
}

#endif // LISTENERS_H
