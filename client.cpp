#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

void client_function(const std::string& client_type) {
    try {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "8080");
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::string message = client_type + "\n";
        boost::asio::write(socket, boost::asio::buffer(message));

        char response[1024];
        size_t reply_length = socket.read_some(boost::asio::buffer(response));
        std::cout << std::string(response, reply_length) << "\n";

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

int main() {
    std::string client_type;
    std::cout << "Enter client type (driver/customer): ";
    std::cin >> client_type;
    while(client_type != "customer" and client_type != "driver"){
        std::cout << "Unknown client type\n";
        std::cin >> client_type;
    }

    client_function(client_type);
    return 0;
}
