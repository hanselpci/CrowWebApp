#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class PathUtils
{
private:
    // split path to components
    static std::vector<std::string> splitPath(const std::string &path);

public:
    static std::string normalizePath(std::string &path);
    static std::string getCurrentDirectory();
    static std::string getAbsolutePath(const std::string &path);
    static bool isAbsolutePath(const std::string &path);
    static std::string getRelativePath(const std::string &base_dir, const std::string &target_path);
    static bool canGenerateRelativePath(const std::string &base_dir, const std::string &target_path);
};