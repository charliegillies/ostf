#pragma once

#include "App.h"
#include <string>

namespace ostf
{
  class ClientApp : public Application
  {
  private:
    std::string _ip;

  public:
    ClientApp(std::string address);
    virtual void run() override;
  };
}
