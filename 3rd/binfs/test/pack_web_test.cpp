#include <string>
#include <fstream>
#include "web_resources.hpp"

int main()
{
    BinFS::BinFS *binfs = new BinFS::BinFS();

    std::string file1 = binfs->get_file("web/index.html");
    std::string file2 = binfs->get_file("web/script.js");

    // write output file
    std::ofstream output("out.html", std::fstream::binary);
    output << file1;

    std::ofstream output2("out.js", std::fstream::binary);
    output2 << file2;

    return 0;
}
