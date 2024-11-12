#include "header/server.h"

void TaxiServer::make_route(){
    auto passenger_socket = passenger_queue.front();
    passenger_queue.pop_front();
    auto driver_socket = driver_queue.front();
    driver_queue.pop_front();
    std::cout << "Маршрут построен!\nВсего водителей: " << driver_queue.size() << "\nВсего пассажиров: " << passenger_queue.size() << "\n";
    std::string driver_message = "У вас новый клиент\n";
    boost::asio::write(*driver_socket, boost::asio::buffer(driver_message));
    std::string passenger_message = "Водитель найден\n";
    boost::asio::write(*passenger_socket, boost::asio::buffer(passenger_message));

    Route route(driver_socket, passenger_socket);
    route.get_address();
    route.start_time = get_moscow_time();
    if(route.manipulate() == true){
        route.end_time = get_moscow_time();
        add_log(route);
        handle_driver(driver_socket);
    }
}