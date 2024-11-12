#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <deque>
#include "route.h"

using boost::asio::ip::tcp;

class TaxiServer {
public:
    TaxiServer(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        std::cout << "Server is running now" << "\n";
        logname = create_log();
        start_accept();
    }
    std::string get_moscow_time();

private:
    std::mutex driver_queue_mutex;
    std::mutex passenger_queue_mutex;
    std::condition_variable cv;
    std::deque<std::shared_ptr<tcp::socket>> passenger_queue;
    std::deque<std::shared_ptr<tcp::socket>> driver_queue; 
    tcp::acceptor acceptor_;
    std::string logname;
    void add_log(Route&);
    void start_accept() ;
    void handle_client(std::shared_ptr<tcp::socket> socket);
    void handle_driver(std::shared_ptr<tcp::socket> socket);
    void handle_passenger(std::shared_ptr<tcp::socket> socket);
    std::string create_log();  
    void make_route();
};