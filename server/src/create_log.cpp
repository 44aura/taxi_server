#include "header/server.h"

std::string TaxiServer::create_log(){
    std::string filename = "serverlog_" + get_moscow_time();
    std::ofstream out(filename);
    return filename;
}