#ifndef _ICCM_CHAOS_CONFIGURATION_H_
#define _ICCM_CHAOS_CONFIGURATION_H_

#include <string>
#include <vector>
#include <fstream>

#include "CHAOS_svnt_export.h"

namespace iCCM
{
  struct Servant_Definition
  {
    std::string alias;
    std::string module;
    std::string symbol;
  };

  // consumes dds:hello
  // publishes rti:hello

  struct Port_Definition
  {
    std::string type;
    std::string source;
    std::string servant;
    std::string destination;
  };

  struct Servant_Configuration
  {
    std::vector <Servant_Definition> servants;
    std::vector <Port_Definition> ports;
  };

  /**
   * @class CHAOS_Servant_Configuration
   */
  class ICCM_CHAOS_SVNT_Export CHAOS_Servant_Configuration
  {
  public:
    /**
     * Initializing constructor.
     */
    CHAOS_Servant_Configuration (const std::string & filename);

    /// Destructor.
    ~CHAOS_Servant_Configuration (void);

    bool operator >>= (Servant_Configuration & config);

  private:
    std::ifstream file_;
  };
}

#endif  // !defined _ICCM_CHAOS_CONFIGURATION_H_
