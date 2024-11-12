#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
using boost::asio::ip::tcp;

struct Route{
    friend class TaxiServer;
public:
    Route(std::shared_ptr<tcp::socket> driver_sock, std::shared_ptr<tcp::socket> passenger_sock): 
        driver_socket{driver_sock},
        passenger_socket{passenger_sock}
        {}

private:
    void get_address();
    bool manipulate();
    bool arrive();
    std::shared_ptr<tcp::socket> driver_socket;
    std::shared_ptr<tcp::socket> passenger_socket;
    std::string from;
    std::string to;
    std::string message;
    std::string response;
    boost::asio::streambuf buff;
    std::string start_time;
    std::string end_time;
};