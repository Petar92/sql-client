#include "/mnt/c/Projects/sql-client/include/sql-client/network/client.hpp"
#include "/mnt/c/Projects/sql-client/include/sql-client/parser/query_parser.hpp"
#include <iostream>

using namespace SqlClient::Client;
using namespace SqlClient::Parser;

bool is_connection_established = false;
ConnectionInfo connection_info;
Client client;
std::string query;
std::unique_ptr<tcp::socket> sql_socket;

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
                sql_socket = client.connect(&connection_info);
                if (sql_socket == nullptr) {
                    break;
                }
                is_connection_established = true;
                std::cout << "Connection established to " << connection_info.host << ":" << connection_info.port << std::endl;
            }
        }
        else {
            try {
                query = QueryParser::parse(user_input);

                std::array<char, 128> buf;
                boost::system::error_code error;
        
                boost::asio::write(*sql_socket, boost::asio::buffer(query));

                size_t len = sql_socket->read_some(boost::asio::buffer(buf), error);
        
                if (error) {
                    is_connection_established = false;
                    if (error != boost::asio::error::eof)
                        std::cerr << "Error reading from the server: " << error << std::endl;
                    break;
                }
        
                std::cout.write(buf.data(), len);
                std::cout << "\n";
            }
            catch (const std::exception& e) {
                std::cerr << "Error processing the query: " << e.what() << std::endl;
            }
        }
    }
    
    return 0;
}