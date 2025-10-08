#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINDOWS 1
#endif

#include <string>
#include <vector>
#include <cstring>
#include <sys/stat.h>
#if !defined(WINDOWS)
#include <dirent.h>
#else
#include <3rdparty/win32/dirent.h>
#endif

#include "cmdline.h"
#include "binfs.h"

std::vector<std::string> get_files(const std::string &path, std::vector<std::string> &paths)
{
  struct stat s;
  if (stat(path.c_str(), &s) == 0)
  {
    if (s.st_mode & S_IFREG)
    {
      paths.push_back(path);
    }
    else if (s.st_mode & S_IFDIR)
    {
      DIR *dir;
      struct dirent *ent;
      if ((dir = opendir(path.c_str())) != NULL)
      {
        while ((ent = readdir(dir)) != NULL)
        {
          std::string found(ent->d_name, strlen(ent->d_name));
          if (found != "." && found != "..")
          {
            found = path + "/" + found;
            get_files(found, paths);
          }
        }
        closedir(dir);
      }
    }
  }

  return paths;
}

int main(int argc, char *argv[])
{
  cmdline::parser arg_parser;
  arg_parser.add<std::string>("outfile", 'o', "output file name", false, "binfs.hpp");
  arg_parser.add<std::string>("base_dir", 'b', "base directory to create relative path", false, "");
  arg_parser.parse_check(argc, argv);

  std::string outfile = arg_parser.get<std::string>("outfile");
  std::string base_dir = arg_parser.get<std::string>("base_dir");
  std::vector<std::string> folders = arg_parser.rest();

  BinFS::BinFS *binfs = new BinFS::BinFS(base_dir);

  std::vector<std::string> files;

  for (const std::string &path : folders)
  {
    files = get_files(path, files);
  }
  try
  {
    for (const std::string &path : files)
    {
      binfs->add_file(path);
    }

    binfs->output_hpp_file(outfile);

    return 0;
  }
  catch (const std::runtime_error &e)
  {
    printf("Error: %s\n", e.what());
    return 1;
  }
}
