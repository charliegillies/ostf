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

  std::cout << "ServerApp - attempting bind on ip " << _ip.c_str() << '\n';
  socket.bind(_ip.c_str());
  std::cout << "Bind passed." << '\n';

  while(true) {
    zmq::message_t request;

    std::cout << "Waiting for Hello.." << '\n';
    socket.recv(&request);
    std::cout << "Received Hello. Replying.." << std::endl;

    sleep(1);

    zmq::message_t reply(5);
    memcpy(reply.data(), "World", 5);
    socket.send(reply);
  }

}
