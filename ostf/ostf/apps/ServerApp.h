#pragma once

#include "App.h"

namespace ostf
{
    /*
     *
     */
    class ServerApp : public Application
    {
    private:
      std::string _ip;

    public:
      ServerApp(std::string address);
      virtual void run() override;
    };
}
