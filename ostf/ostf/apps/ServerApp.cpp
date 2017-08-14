#include "ServerApp.h"
#include <czmq.h>

ostf::ServerApp::ServerApp(std::string address)
{
  _ip = address;
}

void ostf::ServerApp::run()
{
  std::cout << "Server Application - Start" << '\n';

  // We want to wait for clients to connect to us
  zsock_t* pull = zsock_new_pull(_ip.c_str());

  char* str = zstr_recv(pull);
  puts(str);
  zstr_free(&str);

  zsock_destroy(&pull);
}
