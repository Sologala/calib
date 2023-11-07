#pragma once

#include <fstream>
#include <string>
namespace calib
{
namespace filesys
{

inline bool file_exist(std::string &file_path)
{
    std::ifstream in(file_path);
    if (in.is_open())
    {
        return true;
    }
    return false;
}
#include <sys/stat.h>
inline bool makedir(const std::string &file_path)
{
    return mkdir(file_path.c_str(), 0777);
}

#if __LINUX__
// #define USE_BOOST_FILESYSTEM 1
// #ifdef USE_BOOST_FILESYSTEM
#include <boost/filesystem.hpp>
inline bool makedir(const std::string &file_path)
{
    boost::filesystem::path dirPath(file_path);
    return boost::filesystem::create_directory(dirPath);
}
#endif //
} // namespace filesys

} // namespace calib
