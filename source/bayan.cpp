#include "bayan.h"

SearchDuplicate::SearchDuplicate(std::vector<std::string> vscan_dirs, 
								 std::vector<std::string> vexclude_dirs, 
								 std::vector<std::string> vfile_masks_, 
								 size_t block_size, size_t depth_scan, 
								 uintmax_t min_file_size, std::string hasher) {

}

std::unordered_map<std::string, std::vector<std::string>> SearchDuplicate::Duplicates() {
	std::unordered_map<std::string, std::vector<std::string>> result;
	return result;
}
