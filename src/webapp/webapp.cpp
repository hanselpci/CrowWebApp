#include <iostream>

#include "common_const.h"
#include "server.h"
#include "webview.h"

void start_web_view() {
    // Create web view
#ifdef _DEBUG
    webview::webview w(true, nullptr);
#else
    webview::webview w(false, nullptr);
#endif

    // Set window title and size
    w.set_title("Calculator");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);

    // Navigate to the web server
    std::string url = "http://" + CommonConst::WEB_ADDRESS + ":" + std::to_string(CommonConst::WEB_PORT);
    w.navigate(url);

    std::cout << "Client connecting to: " << url << std::endl;

    // Run the web view event loop
    w.run();
}

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

        // Wait for the server to be ready
        while (!server.isRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Start the web view
        start_web_view();

        // Stop the server
        server.stop();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
