#include "ClientApp.h"
#include <zmq.hpp>

#include <cassert>

ostf::ClientApp::ClientApp(std::string address)
{
  _ip = address;
}

void ostf::ClientApp::run()
{
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REQ);

  std::cout << "Connecting to the Hello World server at " << _ip.c_str() << '\n';
  socket.connect(_ip.c_str());

  for(int i = 0; i < 10; ++i)
  {
    zmq::message_t request(5);
    memcpy(request.data(), "Hello", 5);

    std::cout << "Sending hello.. " << i << "..." << '\n';
    socket.send(request);

    zmq::message_t reply;
    socket.recv(&reply);
    std::cout << "Received World " << i << '\n';
  }

}
