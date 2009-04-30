#include "DDS_Utility.h"

#include "ModelDDSDataDcpsC.h"
#include "ModelDDSDataConversion.h"

#include "SubAppDDS.h"

#include "Listeners.h"

namespace DSTO_AppSpace_Impl
{
  app_op_recv_Listener::app_op_recv_Listener (
    ::AppSpace::SubAppDDS * app,
    DDS_Utility & dds_utility)
    : app_ (app),
      dds_utility_ (dds_utility)
  {
  }

  app_op_recv_Listener::~app_op_recv_Listener (void)
  {
  }

  void
  app_op_recv_Listener::on_data_available (DataReader_ptr reader)
  {
    ::Outer::TestData_DDSSeq data_seq;
    SampleInfoSeq info_seq;
    
    ::Outer::TestData_DDSDataReader_var my_reader =
      ::Outer::TestData_DDSDataReader::_narrow (reader);
    
    ReturnCode_t status =
      my_reader->take (data_seq,
                    info_seq,
                    1,
                    ANY_SAMPLE_STATE,
                    ANY_VIEW_STATE,
                    ANY_INSTANCE_STATE);
    this->dds_utility_.check_status (
      status,
      "app_op_recvListener: take()");
      
  //  status = reader->return_loan (data_seq, info_seq);

    ::Outer::TestData * ev = 0;
    ACE_NEW (ev, ::Outer::TestData);
    ModelDDSDataConversion::from_corba (*ev, data_seq[0]);
    
    this->app_->app_op_recv (ev);
  }
}
