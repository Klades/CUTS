#ifndef MODEL_DATA_CONVERSION_H
#define MODEL_DATA_CONVERSION_H

#include "AppData.h"

#include "ModelDataC.h"
#include "ModelData_export.h"

namespace ModelDataConversion
{
  void ModelData_Export
  to_corba ( ::Outer::Inner::Data_IDL &,
            const ::Outer::Inner::Data &);
            
  void ModelData_Export
  from_corba ( ::Outer::Inner::Data &,
              const ::Outer::Inner::Data_IDL &);
            
  void ModelData_Export
  to_corba ( ::Outer::TestData_IDL &,
            const ::Outer::TestData &);
            
  void ModelData_Export
  from_corba ( ::Outer::TestData &,
              const ::Outer::TestData_IDL &);
}

#endif // MODEL_DATA_CONVERSION_H