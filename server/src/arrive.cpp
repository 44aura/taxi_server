#include "header/route.h"

bool Route::arrive(){
    message = "Пункт назначения:" + to + "\nВведите 1, если вы прибыли\n";
    boost::asio::write(*driver_socket, boost::asio::buffer(message));
    while(true){
        boost::asio::read_until(*driver_socket, buff, "\n");
        std::istream is(&buff);
        std::getline(is, response);
        if (response.find("1") != std::string::npos){
            message = "Вы прибыли, спасибо что пользуетесь нашей компанией!\n";
            boost::asio::write(*passenger_socket, boost::asio::buffer(message));
            message = "Поездка окончена. Вы вернулись в очередь.\n";
            boost::asio::write(*driver_socket, boost::asio::buffer(message));
            return true;
        }
    }
}