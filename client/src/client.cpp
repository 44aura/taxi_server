#include "header/client.h"

int main() {
    std::string client_type;
    std::cout << "Enter client type (driver/passenger): ";
    std::cin >> client_type;
    while(client_type != "passenger" and client_type != "driver"){
        std::cout << "Unknown client type\n";
        std::cin >> client_type;
    }
    Client client;
    client.client_function(client_type);
    return 0;
}
