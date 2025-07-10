#pragma once

#include <string>
#include <vector>
#include <memory>

namespace SqlClient::Parser {

class QueryParser {

public:
    QueryParser();
    ~QueryParser();

    static std::string parse(const std::string& query);
};

} 