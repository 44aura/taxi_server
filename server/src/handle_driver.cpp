#include "header/server.h"

void TaxiServer::handle_driver(std::shared_ptr<tcp::socket> socket) {
    std::unique_lock<std::mutex> lock(driver_queue_mutex);
    driver_queue.push_back(socket);
    std::cout << "Водитель добавлен в очередь. Водителей в очереди: " << driver_queue.size() << "\n";
    lock.unlock();
    if (passenger_queue.empty()){
        std::string message = "Очередь пассажиров пуста. Подождите, пожалуйста.\n";
        boost::asio::write(*socket, boost::asio::buffer(message));
        cv.wait(lock);
    }
}