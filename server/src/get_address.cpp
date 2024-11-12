#include "header/route.h"

void Route::get_address(){
    message = "Введите адрес отправления\n";
    boost::asio::write(*passenger_socket, boost::asio::buffer(message));;
    boost::asio::read_until(*passenger_socket, buff, "\n");
    std::istream is(&buff);
    std::getline(is, response);
    from = response;

    message = "Введите адрес прибытия\n";
    boost::asio::write(*passenger_socket, boost::asio::buffer(message));;
    boost::asio::read_until(*passenger_socket, buff, "\n");
    std::getline(is, response);
    to = response;
    
    message = "Приятной поездки!\n";
    boost::asio::write(*passenger_socket, boost::asio::buffer(message));;
}