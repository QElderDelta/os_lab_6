#pragma once

#include <zmq.hpp>
#include <unistd.h>
#include <string>

bool SendMessage(zmq::socket_t& socket, const std::string& message);

std::string RecieveMessage(zmq::socket_t& socket);

int BindSocket(zmq::socket_t& socket);

void CreateNode(int id, int portNumber);
