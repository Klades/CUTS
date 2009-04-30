#ifndef MODEL_DATA_CONVERSION_H
#define MODEL_DATA_CONVERSION_H

#include "AppData.h"

#include "ModelDDSDataC.h"
#include "ModelDDSData_export.h"

namespace ModelDDSDataConversion
{
  void ModelDDSData_Export
  to_corba ( ::Outer::Inner::Data_DDS &,
            const ::Outer::Inner::Data &);
            
  void ModelDDSData_Export
  from_corba ( ::Outer::Inner::Data &,
              const ::Outer::Inner::Data_DDS &);
            
  void ModelDDSData_Export
  to_corba ( ::Outer::TestData_DDS &,
            const ::Outer::TestData &);
            
  void ModelDDSData_Export
  from_corba ( ::Outer::TestData &,
              const ::Outer::TestData_DDS &);
}

#endif // MODEL_DATA_CONVERSION_H