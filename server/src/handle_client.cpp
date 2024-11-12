#include "header/server.h"

void TaxiServer::handle_client(std::shared_ptr<tcp::socket> socket) {
    try {
        std::string client_type;
        boost::asio::streambuf buff;
        boost::asio::read_until(*socket, buff, "\n");
        std::istream is(&buff);
        std::getline(is, client_type);

        if (client_type == "driver") {
            std::string message = "Привет, водитель\n";
            boost::asio::write(*socket, boost::asio::buffer(message));
            handle_driver(socket);
        } else if (client_type == "passenger") {
            std::string message = "Привет, пассажир\n";
            boost::asio::write(*socket, boost::asio::buffer(message));

            std::unique_lock<std::mutex> lock(passenger_queue_mutex);
            passenger_queue.push_back(socket);
            std::cout << "Пассажир добавлен в очередь. Пассажиров в очереди: " << passenger_queue.size() << "\n";
            lock.unlock();
        }
        if(!passenger_queue.empty() and !driver_queue.empty()){
            make_route();
        }

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}