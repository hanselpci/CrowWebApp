#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <crow_all.h>
#include "common_const.h"

// Handles API requests for the application
class ApiHandler {
public:
    // Constructor
    ApiHandler() = default;

    // Destructor
    ~ApiHandler() = default;

    // Handles addition request
    crow::response handleAddition(const crow::request& req);

private:
    // Validates if a string represents a valid number
    bool isValidNumber(const std::string& str);
};

#endif // API_HANDLER_H
