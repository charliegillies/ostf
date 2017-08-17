#include "ServerApp.h"
#include <zmq.hpp>

#ifndef _WIN32
#include <unistd.h>
#endif

ostf::ServerApp::ServerApp(std::string address)
{
  _ip = address;
}

void ostf::ServerApp::run()
{
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REP);

  char* ip = _ip.c_str();
  std::cout << "ServerApp - attempting bind on ip " << ip << '\n';
  socket.bind(ip);
  std::cout << "Bind passed." << '\n';

  while(true) {
    zmq::message_t request;

    socket.recv(&request);
    std::cout << "Received Hello" << std::endl;

    sleep(1);

    zmq::message_t reply(5);
    memcpy(reply.data(), "World", 5);
    socket.send(reply);
  }

}
