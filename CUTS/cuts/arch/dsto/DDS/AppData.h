#ifndef APPLICATION_DATA_H
#define APPLICATION_DATA_H

#include "ModelDDSData_export.h"

namespace Outer
{
  namespace Inner
  {
    struct ModelDDSData_Export Data
    {
      char * name;
      long id;
      bool urgent;
    };
  }
  
  struct ModelDDSData_Export TestData
  {
    unsigned short key;
    Inner::Data packet;
  };
}
 
#endif // APPLICATION_DATA_H