#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <deque>
#include <string>
#include <mutex>

using boost::asio::ip::tcp;
std::mutex driver_queue_mutex;
std::deque<tcp::socket> driver_queue;  

class TaxiServer {
public:
    TaxiServer(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        start_accept();
    }

private:
    void start_accept() {
        while (true) {  
            tcp::socket socket(acceptor_.get_executor());
            
            acceptor_.accept(socket);
            
            // Запуск потока для обработки каждого клиента
            std::thread(&TaxiServer::handle_client, this, std::move(socket)).detach();
        }
    }

    void handle_client(tcp::socket socket) {
        try {
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, "\n");

            std::istream is(&buffer);
            std::string client_type;
            std::getline(is, client_type);

            if (client_type == "driver") {
                handle_driver(std::move(socket));
            } else if (client_type == "customer") {
                handle_customer(std::move(socket));
            }
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void handle_driver(tcp::socket socket) {
        std::unique_lock<std::mutex> lock(driver_queue_mutex);
        driver_queue.push_back(std::move(socket));
        std::cout << "Driver added to the queue. Total drivers: " << driver_queue.size() << std::endl;
    }

    void handle_customer(tcp::socket socket) {
        std::unique_lock<std::mutex> lock(driver_queue_mutex);
        if (driver_queue.empty()) {
            std::string message = "No drivers available. Please wait...\n";
            boost::asio::write(socket, boost::asio::buffer(message));
        } else {
            tcp::socket driver_socket = std::move(driver_queue.front());
            driver_queue.pop_front();
            std::cout << "Driver assigned to customer. Remaining drivers: " << driver_queue.size() << std::endl;

            std::string customer_message = "Driver found! Driver is on the way.\n";
            boost::asio::write(socket, boost::asio::buffer(customer_message));

            std::string driver_message = "You have a new customer!\n";
            boost::asio::write(driver_socket, boost::asio::buffer(driver_message));
        }
    }

    tcp::acceptor acceptor_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        TaxiServer server(io_context, 8080);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
