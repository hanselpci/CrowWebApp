#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "web_resources.hpp"

namespace BinFS
{
    extern int bin_fs_initialized;
    extern std::vector<std::pair<std::string, std::string>> bin_fs_files;

    class BinFS
    {
    private:
        bool initialized = false;
        std::string hex_to_string(const std::string &in)
        {
            std::string output;
            if ((in.length() % 2) != 0)
            {
                throw std::runtime_error("string is not valid length!");
            }
            size_t cnt = in.length() / 2;
            for (size_t i = 0; cnt > i; ++i)
            {
                uint32_t s = 0;
                std::stringstream ss;
                ss << std::hex << in.substr(i * 2, 2);
                ss >> s;
                output.push_back(static_cast<unsigned char>(s));
            }
            return output;
        }

    public:
        BinFS() { init(); };
        ~BinFS() {};
        std::string get_file(const std::string &filename)
        {
            auto it = bin_fs_files.begin();
            if (!initialized)
            {
                throw std::runtime_error("BinFS not initialized!");
            }
            for (const std::pair<std::string, std::string> &file : bin_fs_files)
            {
                if (file.first == filename)
                {
                    return hex_to_string(file.second);
                }
                it++;
            }
            throw std::runtime_error(filename + " not found!");
        }
        void init()
        {
            initialized = (bin_fs_initialized);
        }
    };
} // namespace BinFS

int main()
{
    BinFS::BinFS *binfs = new BinFS::BinFS();

    try
    {
        std::string file1 = binfs->get_file("index.html");
        std::string file2 = binfs->get_file("script.js");

        // write output file
        std::ofstream output("out.html", std::fstream::binary);
        output << file1;

        std::ofstream output2("out.js", std::fstream::binary);
        output2 << file2;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
