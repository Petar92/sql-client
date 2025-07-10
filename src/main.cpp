#include "/mnt/c/Projects/sql-client/include/sql-client/network/client.hpp"
#include "/mnt/c/Projects/sql-client/include/sql-client/parser/query_parser.hpp"
#include <iostream>

using namespace SqlClient::Client;
using namespace SqlClient::Parser;

bool is_connection_established = false;
ConnectionInfo connection_info;
Client client;
std::string query;

int main() {
    std::string user_input;
    std::cout << "Welcome to the SQL client. Type 'exit' to quit." << std::endl;

    while (true) {
        std::cout << (is_connection_established ? "sql> " : "connect> ");
        std::getline(std::cin, user_input);

        if (user_input == "exit" || std::cin.eof()) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        if (user_input.empty()) {
            continue;
        }
        
        if (!is_connection_established) {
            connection_info = Client::parse_connection_string(user_input);
            if (connection_info.is_valid_connection) {
                is_connection_established = true;
                std::cout << "Connection established to " << connection_info.host << ":" << connection_info.port << std::endl;
            }
        }
        else {
            try {
                query = QueryParser::parse(user_input);
                // TODO: send query to server using boost asio
            }
            catch (const std::exception& e) {
                std::cerr << "Failed to parse query: " << e.what() << std::endl;
            }
        }
    }
    
    return 0;
}