#pragma once

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/unordered_set.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "file.h"
#include "hash.h"

namespace fs = boost::filesystem;

class SearchDuplicate
{
public:
	SearchDuplicate(std::vector<std::string> include_dirs, std::vector<std::string> exclude_dirs, std::vector<std::string> vec_file_mask,
					size_t block_size, size_t scan_depth, uintmax_t min_file_size, std::string hasher);
	std::unordered_map<std::string, std::vector<std::string>> map_find_duplicates();
	void set_include_dirs(std::vector<std::string> dirs);
	void set_exclude_dirs(std::vector<std::string> dirs);
private:
	std::vector<fs::path> include_dirs;
	std::vector<fs::path> exclude_dirs;
	std::vector<boost::regex> vec_reg_filemasks;
	size_t block_size;
	size_t scan_depth;
	uintmax_t min_file_size;
	std::vector<File> files;
	std::unordered_set<std::string> files_canonical;
	IHasher* hasher;
	void set_hasher(std::string hash_str);
	bool excluded_path(fs::path p);
	bool filename_with_filemask(const std::string& filename);
	void add_file(fs::path p);
	void add_filtered_file(fs::path p);
	void scan_path(fs::path p, size_t depth);
	void search();
};
