#pragma once

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/unordered_set.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace fs = boost::filesystem;

class SearchDuplicate
{
    std::vector<fs::path> vscan_dirs;
    std::vector<fs::path> vexclude_dirs;
    std::vector<boost::regex> vfile_masks;
    size_t block_size;
    size_t depth_scan;
    uintmax_t min_file_size;
    std::string hasher;
public:
    SearchDuplicate(std::vector<std::string> vscan_dirs,
                      std::vector<std::string> vexclude_dirs, 
                      std::vector<std::string> vfile_masks_,
                      size_t block_size, size_t depth_scan, 
                      uintmax_t min_file_size, 
                      std::string hasher);
    std::unordered_map<std::string, std::vector<std::string>> Duplicates();
 };

