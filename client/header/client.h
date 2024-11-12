#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std::chrono_literals;
using boost::asio::ip::tcp;

struct Client{
public:
void client_function(const std::string&);
};