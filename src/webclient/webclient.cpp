#include <iostream>
#include <string>
#include "webview.h"
#include "common_const.h"

// Web client desktop application
int main() {
    try {
        std::cout << "Starting standalone web client..." << std::endl;

        // Create web view
        webview::webview w(true, nullptr);

        // Set window title and size
        w.set_title("Addition Calculator");
        w.set_size(800, 600, WEBVIEW_HINT_NONE);

        // Navigate to the web server
        std::string url = "http://" + CommonConst::WEB_ADDRESS + ":" + std::to_string(CommonConst::WEB_PORT);
        w.navigate(url);

        std::cout << "Client connecting to: " << url << std::endl;

        // Run the web view event loop
        w.run();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
