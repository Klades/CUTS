#include "iCCM_Plugin.h"

namespace iCCM
{
  iCCM_Plugin::iCCM_Plugin (std::string name)
  {
    name_ = name;
  }

  iCCM_Plugin::~iCCM_Plugin (void)
  {
  }

  std::string iCCM_Plugin::name (void)
  {
    return this->name_;
  }

  void iCCM_Plugin::destroy (void)
  {
    delete this;
  }
}