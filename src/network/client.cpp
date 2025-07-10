#include "sql-client/network/client.hpp"
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace SqlClient::Client {

Client::Client() {

}
Client::~Client() = default;

/**
 * @brief Parses the initial command which is expected to be
 * a connection string in the format user@host:port
 */
ConnectionInfo Client::parse_connection_string(const std::string& input) {
    auto at_pos = input.find('@');
    auto colon_pos = input.find(':', at_pos);
    ConnectionInfo connection_info;

    if (at_pos == std::string::npos || colon_pos == std::string::npos || at_pos == 0 || colon_pos <= at_pos + 1) {
        std::cerr << "Invalid connection string format. Expected: username@host:port" << std::endl;
        return connection_info;
    }

    connection_info.username = input.substr(0, at_pos);
    connection_info.host = input.substr(at_pos + 1, colon_pos - at_pos - 1);
    connection_info.port = input.substr(colon_pos + 1);
    
    if (connection_info.username.empty() || connection_info.host.empty() || connection_info.port.empty()) {
        std::cerr << "Invalid connection string format. Expected: user@host:port" << std::endl;
    }
    else {
        connection_info.is_valid_connection = true;
    }
    return connection_info;
}

}
