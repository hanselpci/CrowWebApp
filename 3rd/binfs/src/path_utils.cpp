#include "path_utils.h"

#ifdef _WIN32
#include <windows.h>
const char PATH_SEPARATOR = '\\';
#else
#include <unistd.h>
#include <limits.h>
const char PATH_SEPARATOR = '/';
#endif

// split path to components
std::vector<std::string> PathUtils::splitPath(const std::string &path)
{
    std::vector<std::string> components;
    std::stringstream ss(path);
    std::string component;

    while (std::getline(ss, component, PATH_SEPARATOR))
    {
        if (!component.empty())
        {
            components.push_back(component);
        }
    }

    return components;
}

std::string PathUtils::normalizePath(std::string &path)
{
    // use forward slash for path separator
    for (char &c : path)
    {
        if (c == '\\')
        {
            c = '/';
        }
    }
    return path;
}

/**
 * Get the current working directory
 * @return String containing the current working directory path
 * @throws std::runtime_error if getting directory fails
 */
std::string PathUtils::getCurrentDirectory()
{
#ifdef _WIN32
    // Windows implementation
    char buffer[MAX_PATH];
    DWORD length = GetCurrentDirectoryA(MAX_PATH, buffer);

    if (length == 0)
    {
        throw std::runtime_error("Failed to get current directory");
    }

    // Handle case where path length exceeds buffer size
    if (length > MAX_PATH)
    {
        std::string larger_buffer(length + 1, '\0');
        length = GetCurrentDirectoryA(length + 1, &larger_buffer[0]);
        if (length == 0)
        {
            throw std::runtime_error("Failed to get current directory");
        }
        larger_buffer.resize(length);
        return larger_buffer;
    }

    return std::string(buffer, length);
#else
    // Unix-like systems implementation
    const size_t buffer_size = 1024;
    char buffer[buffer_size];

    if (getcwd(buffer, buffer_size) == nullptr)
    {
        // If buffer is too small, try dynamically allocating a larger one
        size_t larger_size = buffer_size * 2;
        while (true)
        {
            char *larger_buffer = new char[larger_size];
            if (getcwd(larger_buffer, larger_size) != nullptr)
            {
                std::string result(larger_buffer);
                delete[] larger_buffer;
                return result;
            }

            if (errno != ERANGE)
            {
                delete[] larger_buffer;
                throw std::runtime_error("Failed to get current directory: " + std::string(std::strerror(errno)));
            }

            delete[] larger_buffer;
            larger_size *= 2;
        }
    }

    return std::string(buffer);
#endif
}

// Get absolute path
std::string PathUtils::getAbsolutePath(const std::string &path)
{
#ifdef _WIN32
    char absolute_path[MAX_PATH];
    if (GetFullPathNameA(path.c_str(), MAX_PATH, absolute_path, NULL))
    {
        return std::string(absolute_path);
    }
#else
    char absolute_path[PATH_MAX];
    if (realpath(path.c_str(), absolute_path))
    {
        return std::string(absolute_path);
    }
#endif
    return path; // Return original path if failed
}

bool PathUtils::isAbsolutePath(const std::string &path)
{
    if (path.empty())
        return false;

#ifdef _WIN32
    // Check driver letter if the path is absolute on Windows
    if (path.length() >= 3)
    {
        bool hasDriveLetter = std::isalpha(static_cast<unsigned char>(path[0])) && path[1] == ':';
        bool hasSeparator = path[2] == '\\' || path[2] == '/';

        if (hasDriveLetter && hasSeparator)
        {
            return true;
        }
    }

    // Check UNC path (\\server\share)
    if (path.length() >= 2 && path[0] == '\\' && path[1] == '\\')
    {
        return true;
    }

    // Check Unix-style path (e.g., /path/to/file)
    if (path[0] == '/')
    {
        return true;
    }

    return false;
#else
    // Check Unix-style path (e.g., /path/to/file)
    return path[0] == '/';
#endif
}
std::string PathUtils::getRelativePath(const std::string &base_dir, const std::string &target_path)
{
    // Get absolute paths
    std::string abs_base = getAbsolutePath(base_dir);
    std::string abs_target = getAbsolutePath(target_path);

    // Split paths to components
    std::vector<std::string> base_components = splitPath(abs_base);
    std::vector<std::string> target_components = splitPath(abs_target);

    // Get common prefix components
    size_t common_length = 0;
    size_t min_length = (std::min)(base_components.size(), target_components.size());

    for (size_t i = 0; i < min_length; ++i)
    {
        if (base_components[i] != target_components[i])
        {
            break;
        }
        common_length++;
    }

    // If there is no common prefix, cannot generate relative path
    if (common_length == 0)
    {
        return "";
    }

    // Build relative path
    std::string result;

    // For remaining parts in base path, each directory needs a ".."
    for (size_t i = common_length; i < base_components.size(); ++i)
    {
        if (!result.empty())
        {
            result += PATH_SEPARATOR;
        }
        result += "..";
    }

    // Add remaining parts in target path
    for (size_t i = common_length; i < target_components.size(); ++i)
    {
        if (!result.empty())
        {
            result += PATH_SEPARATOR;
        }
        result += target_components[i];
    }

    // If result is empty, return current directory "."
    if (result.empty())
    {
        return ".";
    }

    return normalizePath(result);
}

// Check if relative path can be generated
bool PathUtils::canGenerateRelativePath(const std::string &base_dir, const std::string &target_path)
{
    std::string abs_base = getAbsolutePath(base_dir);
    std::string abs_target = getAbsolutePath(target_path);

    // On Windows, check if drive letters are the same
#ifdef _WIN32
    if (abs_base.size() >= 2 && abs_target.size() >= 2)
    {
        if (abs_base[0] != abs_target[0] || abs_base[1] != ':')
        {
            return false;
        }
    }
#endif

    std::vector<std::string> base_components = splitPath(abs_base);
    std::vector<std::string> target_components = splitPath(abs_target);

    // If there is at least one common component, relative path can be generated
    return !base_components.empty() && !target_components.empty() &&
           base_components[0] == target_components[0];
}
