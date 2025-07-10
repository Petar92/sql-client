#include "sql-client/parser/query_parser.hpp"
#include <iostream>
#include <pg_query.h>

namespace SqlClient::Parser {

QueryParser::QueryParser() {}
QueryParser::~QueryParser() {}

std::string QueryParser::parse(const std::string& query) {
    PgQueryParseResult result;
    result = pg_query_parse(query.c_str());
    if (result.error) {
        std::string error_message(result.error->message);
        pg_query_free_parse_result(result);
        throw std::runtime_error(error_message);
    }

    std::string parse_result(result.parse_tree);
    pg_query_free_parse_result(result);
    return parse_result;
}

}
