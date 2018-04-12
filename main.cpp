#include <iostream>
#include "include/TConsole.h"
#include "include/network_asio.h"

int main(int argc, char** argv)
{
    if(argc<3){
        std::cout << "Usage: bulk_server <port> <bulk_size>" << std::endl;
        return -1;
    };

    int port = std::stoi(argv[1]);
    int bulk_size = std::stoi(argv[2]);

    boost::asio::ip::tcp::endpoint ep( boost::asio::ip::tcp::v4(), port);
    boost::asio::io_service service;

    network::server host(service, ep, std::make_shared<TConsole>(bulk_size));

    service.run();

    return 0;
}
