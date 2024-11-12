#include "header/route.h"

bool Route::manipulate(){
    message = "Адрес отправления:" + from + "\nВведите 1, если находитесь на адресе\n";
    boost::asio::write(*driver_socket, boost::asio::buffer(message));;
    while(true){
        boost::asio::read_until(*driver_socket, buff, "\n");
        std::istream is(&buff);
        std::getline(is, response);
        if (response.find("1") != std::string::npos){
            return arrive();
        }
    }
}