#ifndef COMMON_CONST_H
#define COMMON_CONST_H

#include <string>

// Common constants used across the application
namespace CommonConst {
    // Default port for the web server
    constexpr int WEB_PORT = 8080;

    // Default web server address
    const std::string WEB_ADDRESS = "127.0.0.1";

    // Path to web resources
    const std::string WEB_RESOURCES_PATH = "web/";
}

#endif // COMMON_CONST_H
