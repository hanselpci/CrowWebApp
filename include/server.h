#ifndef SERVER_H
#define SERVER_H

#include <crow_all.h>
#include "api_handler.h"
#include "common_const.h"
#include <string>
#include <atomic>

#if WEB_RESOURCE_PACKED == 1
#include "web_resources.hpp"
#endif

// Web server class that handles HTTP requests and serves web content
class Server
{
public:
    // Constructor with optional port specification
    explicit Server(int port = CommonConst::WEB_PORT, std::string host = CommonConst::WEB_ADDRESS);

    // Destructor
    ~Server();

    // Starts the server in a separate thread
    void start();

    // Stops the server
    void stop();

    // Checks if the server is running
    bool isRunning() const;

    // Gets the port the server is running on
    int getPort() const;

    // Gets the host address the server is bound to
    std::string getAddress() const;

private:
#if WEB_RESOURCE_PACKED == 1
    BinFS::BinFS *binfs = nullptr;
#endif
    // Sets up all the routes for the server
    void setupRoutes();

    // Crow web application instance
    crow::SimpleApp app_;

    // API handler instance
    ApiHandler apiHandler_;

    // Port number
    int port_;

    // Host address
    std::string address_;

    // Flag indicating if server is running
    std::atomic<bool> isRunning_;

    // Thread for running the server
    std::thread serverThread_;
};

#endif // SERVER_H
