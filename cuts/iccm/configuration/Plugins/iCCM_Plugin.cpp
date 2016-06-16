#include "iCCM_Plugin.h"

namespace iCCM
{
  Plugin::Plugin (std::string name)
  {
    name_ = name;
  }

  Plugin::~Plugin (void)
  {
  }

  std::string Plugin::name (void)
  {
    return this->name_;
  }

  void Plugin::destroy (void)
  {
    delete this;
  }
}