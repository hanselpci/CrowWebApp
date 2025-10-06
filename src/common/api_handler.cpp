#include "api_handler.h"
#include <regex>

// Handles addition of two numbers received in JSON format
crow::response ApiHandler::handleAddition(const crow::request& req) {
    try {
        // Parse JSON from request body
        auto json = crow::json::load(req.body);

        // Check if JSON parsing was successful
        if (!json) {
            return crow::response(400, crow::json::wvalue{{"error", "Invalid JSON format"}});
        }

        // Extract numbers from JSON
        std::string num1Str = json["num1"].s();
        std::string num2Str = json["num2"].s();

        // Validate input numbers
        if (!isValidNumber(num1Str) || !isValidNumber(num2Str)) {
            return crow::response(400, crow::json::wvalue{{"error", "Invalid number format"}});
        }

        // Convert to doubles and calculate sum
        double num1 = std::stod(num1Str);
        double num2 = std::stod(num2Str);
        double result = num1 + num2;

        // Return result as JSON
        return crow::response(crow::json::wvalue{{"result", result}});
    }
    catch (const std::exception& e) {
        return crow::response(500, crow::json::wvalue{{"error", e.what()}});
    }
}

// Validates if a string is a valid number (integer or floating point)
bool ApiHandler::isValidNumber(const std::string& str) {
    // Regular expression to match numbers
    const std::regex numberRegex("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");
    return std::regex_match(str, numberRegex);
}
