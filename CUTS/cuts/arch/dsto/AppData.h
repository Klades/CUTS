#ifndef APPLICATION_DATA_H
#define APPLICATION_DATA_H

#include "ModelData_export.h"

namespace Outer
{
  namespace Inner
  {
    struct ModelData_Export Data
    {
      char * name;
      long id;
      bool urgent;
    };
  }
  
  struct ModelData_Export TestData
  {
    unsigned short key;
    Inner::Data packet;
  };
}
 
#endif // APPLICATION_DATA_H