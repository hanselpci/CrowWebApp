#ifndef _BINFS_H_
#define _BINFS_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>

namespace BinFS
{
  const int BINFS_CHUNK_SIZE = 78;

  class BinFS
  {
  private:
    std::string base_dir;
    std::vector<std::pair<std::string, std::string>> files;

    bool file_exists(const std::string &filename);
    std::string read_file(const std::string &filename);
    std::string string_to_hex(const std::string &in);
    std::string hex_to_string(const std::string &in);

  public:
    BinFS(std::string base_dir_ = "");
    ~BinFS();

    void add_file(const std::string &filename);
    void remove_file(const std::string &filename);
    std::string get_file(const std::string &filename);
    void output_hpp_file(const std::string &filename, int chunk_size = BINFS_CHUNK_SIZE);
    void output_hpp_file_lite(const std::string &filename, int chunk_size = BINFS_CHUNK_SIZE);
  };

} // BinFS

#endif // _BINFS_H_
