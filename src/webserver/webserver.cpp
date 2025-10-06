#include <iostream>
#include "server.h"
#include "common_const.h"

// Web server console application
int main() {
    try {
        std::cout << "Starting standalone web server..." << std::endl;

        // Create and start the server
        Server server(CommonConst::WEB_PORT);
        server.start();

        std::cout << "Server running on http://" << CommonConst::WEB_ADDRESS
                  << ":" << server.getPort() << std::endl;
        std::cout << "Press Enter to stop server..." << std::endl;

        // Wait for user input to stop
        std::cin.get();

        // Stop the server
        server.stop();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
