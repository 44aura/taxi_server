#include <boost/asio.hpp>
#include <iostream>
#include "header/server.h"

int main() {
    try {
        boost::asio::io_context io_context;
        TaxiServer server(io_context, 8080);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
