#pragma once

#include <string>

struct ConnectionInfo {
    std::string username;
    std::string host;
    std::string port;
    bool is_valid_connection = false;
};