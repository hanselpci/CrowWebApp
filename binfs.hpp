#ifndef _BINFS_OUTPUT_HPP_
#define _BINFS_OUTPUT_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace BinFS
{

class BinFS
{
private:
  std::vector<std::pair<std::string, std::string>> files;
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
  BinFS() {};
  ~BinFS() {};
  std::string get_file(const std::string &filename)
  {
    auto it = files.begin();
    for (const std::pair<std::string, std::string> &file : files)
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
  }
};

} // BinFS

#endif // _BINFS_OUTPUT_HPP_

