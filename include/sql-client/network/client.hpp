#pragma once

#include "connection_info.hpp"
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace SqlClient::Client {

class Client {

public:
    boost::asio::io_context io_context;
    
    Client();
    ~Client();

    std::unique_ptr<tcp::socket> connect(ConnectionInfo* connection_info);
    static ConnectionInfo parse_connection_string(const std::string& input);
};

}