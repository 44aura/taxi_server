#include "header/server.h"

void TaxiServer::start_accept(){
    while (true) {  
        auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor());        
        acceptor_.accept(*socket);        
        std::thread(&TaxiServer::handle_client, this, socket).detach();
    }
}