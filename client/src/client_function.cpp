#include "header/client.h"

void Client::client_function(const std::string& client_type) {
    try {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "8080");
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::string message = client_type + "\n";
        socket.write_some(boost::asio::buffer(message));

        char response[1024];
        while(true){
            size_t reply_length = socket.read_some(boost::asio::buffer(response));
            std::string server_message(response, reply_length);
            std::cout << server_message;
            if (server_message.find("Введите адрес отправления") != std::string::npos || server_message.find("Введите адрес прибытия") != std::string::npos || server_message.find("Введите 1") != std::string::npos){
                std::cin >> message;
                socket.write_some(boost::asio::buffer(message + "\n"));
            }
            if (server_message.find("Вы прибыли") != std::string::npos){
                break;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}