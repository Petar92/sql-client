#pragma once

#include "connection_info.hpp"
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace SqlClient::Client {

class Client {

public:
    Client();
    ~Client();

    static ConnectionInfo parse_connection_string(const std::string& input);
};

}