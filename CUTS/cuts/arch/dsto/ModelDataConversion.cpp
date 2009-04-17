#include "FromCORBA.h"
#include "ToCORBA.h"

#include "ModelDataConversion.h"

namespace ModelDataConversion
{
  void to_corba ( ::Outer::Inner::Data_IDL & to,
                 const ::Outer::Inner::Data & from)
  {
    ToCORBA::copy (&to.name, from.name);
    ToCORBA::copy (&to.id, from.id);
    ToCORBA::copy (&to.urgent, from.urgent);
  }
  
  void from_corba ( ::Outer::Inner::Data & to,
                   const ::Outer::Inner ::Data_IDL & from)
  {
    FromCORBA::copy (&to.name, from.name);
    FromCORBA::copy (&to.id, from.id);
    FromCORBA::copy (&to.urgent, from.urgent);
  }
  
  void to_corba ( ::Outer::TestData_IDL & to,
                 const ::Outer::TestData & from)
  {
    to.key (from.key);
    to_corba (to.packet (), from.packet);
  }
  
  void from_corba ( ::Outer::TestData & to,
                   const ::Outer::TestData_IDL & from)
  {
    FromCORBA::copy (&to.key, from.key ());
    from_corba (to.packet, from.packet ());
  }
}