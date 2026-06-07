#include <template/header_only.h>
#include <iostream>
#include <sg/tcp_server.h>

using namespace sg::net;

int main(int, char**) {
    // callback for when a client connects
    tcp_server::session_created_cb_t onClientConnected = [&](tcp_server&, auto) {
        std::cout << "Client connected" << std::endl;
    };

    // callback for when a client disconnects
    tcp_server::session_disconnected_cb_t onClientDisconnected =
        [&](tcp_server&, auto, auto) { std::cout << "Client disconnected" << std::endl; };

    // callback for when data is available from client
    tcp_server::session_data_available_cb_t onDataReceived =
        [](tcp_server& l, auto id, const auto* data, size_t size) { l.write(id, data, size); };

    end_point ep("127.0.0.1", 55555);

    tcp_server server;
    tcp_server::CallBacks callbacks;
    callbacks.OnSessionCreated = onClientConnected;
    callbacks.OnSessionDataAvailable = onDataReceived;
    callbacks.OnDisconnected = onClientDisconnected;
    server.start({ep}, callbacks);

    // Wait until server is stopped
    server.future_get_once();

    return 0;
}
