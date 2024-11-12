#include "header/server.h"

void TaxiServer::add_log(Route& route){
    std::ofstream out;
    out.open(logname, std::ios::app);
    if (out.is_open()){
        out << "Адрес отправления: " << route.from 
        << ". Адрес прибытия: " << route.to
        << ". Время отправления: " << route.start_time
        << ". Время прибытия: " << route.end_time << "\n";
        out.close();
    }
}