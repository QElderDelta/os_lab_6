#include "socketRoutine.hpp"
#include <iostream>

bool SendMessage(zmq::socket_t& socket, const std::string& message) {
    zmq::message_t m(message.size());
    memcpy(m.data(), message.c_str(), message.size());
    return socket.send(m);
}

std::string RecieveMessage(zmq::socket_t& socket) {
    zmq::message_t message;
    bool messageRecieved;
    try {
        messageRecieved = socket.recv(&message);
    } catch(...) {
        messageRecieved = false;
    }
    std::string recieved(static_cast<char*>(message.data()), message.size());

    if(!messageRecieved || recieved.empty()) {
        return "Error: Node is unavailable";
    } else {
        return recieved;
    }
}

int BindSocket(zmq::socket_t& socket) {
    int port = 50000;
    std::string portTemplate = "tcp://127.0.0.1:";
    while(true) {
        try {
            socket.bind(portTemplate + std::to_string(port));
            break;
        } catch(...) {
            port++;
        }
    }
    return port;
}

void CreateNode(int id, int portNumber) {
    char* arg0 = strdup("./calcNode");
    char* arg1 = strdup((std::to_string(id)).c_str());
    char* arg2 = strdup((std::to_string(portNumber)).c_str());
    char* args[] = {arg0, arg1, arg2, NULL};
    execv("./calcNode", args);
}
