#pragma once

#include <iostream>

namespace ostf
{
  /*
   * Base class for a simple run() application.
   * Pretty much just being used for examples.
   */
  class Application
  {
  public:
    virtual void run() = 0;
  };
}
