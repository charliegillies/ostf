#include "ClientApp.h"
#include <czmq.h>

ostf::ClientApp::ClientApp(std::string address)
{
  _ip = address;
}

void ostf::ClientApp::run()
{
  std::cout << "Client Application - Start" << '\n';

  // We want to connect to the server
  zsock_t* push = zsock_new_push(_ip.c_str());

  zstr_send(push, "Hello, World");

  zsock_destroy(&push);
}
