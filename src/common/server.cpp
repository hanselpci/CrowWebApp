#include "server.h"
#include <thread>
#include <iostream>

// Constructor
Server::Server(int port) : port_(port), isRunning_(false) {
    setupRoutes();
}

// Destructor
Server::~Server() {
    stop();
}

// Starts the server in a separate thread
void Server::start() {
    if (!isRunning_) {
        isRunning_ = true;
        serverThread_ = std::thread([this]() {
            try {
                std::cout << "Starting server on port " << port_ << std::endl;
                app_.port(port_).multithreaded().run();
            }
            catch (const std::exception& e) {
                std::cerr << "Server error: " << e.what() << std::endl;
                isRunning_ = false;
            }
        });
    }
}

// Stops the server
void Server::stop() {
    if (isRunning_) {
        isRunning_ = false;
        app_.stop();
        if (serverThread_.joinable()) {
            serverThread_.join();
        }
        std::cout << "Server stopped" << std::endl;
    }
}

// Checks if the server is running
bool Server::isRunning() const {
    return isRunning_;
}

// Gets the port number
int Server::getPort() const {
    return port_;
}

// Sets up all the routes
void Server::setupRoutes() {
    // API endpoint for addition
    CROW_ROUTE(app_, "/api/add")
        .methods("POST"_method)([this](const crow::request& req) {
            return apiHandler_.handleAddition(req);
        });

    // Serve static files from web directory without requiring /web in the path
    CROW_ROUTE(app_, "/<path>")
        .methods("GET"_method)([](const std::string& path) {
            std::string fullPath = CommonConst::WEB_RESOURCES_PATH + path;
            crow::response res;
            res.set_static_file_info(fullPath);
            return res;
        });

    // Default route to serve index.html
    CROW_ROUTE(app_, "/")
        .methods("GET"_method)([]() {
            std::string indexPath = CommonConst::WEB_RESOURCES_PATH + "index.html";
            crow::response res;
            res.set_static_file_info(indexPath);
            return res;
        });
}
