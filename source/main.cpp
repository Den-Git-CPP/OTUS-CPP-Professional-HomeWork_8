#include <boost/program_options.hpp>
#include <exception>
#include <iostream>
#include "bayan.h"

namespace std {
	std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& vec) {
		for(const auto& elem : vec) {
			os << elem << " ";
		}
		return os;
	}

}

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
	try {
		po::options_description desc{"Options"};
		desc.add_options()
			("help,h", "Help screen")
			("include,I", po::value<std::vector<std::string>>()->multitoken(), "Directories to scan")
			("exclude,E", po::value<std::vector<std::string>>()->multitoken()->default_value(std::vector<std::string>{}), "Directories to exclude")
			("depth_scan,D", po::value<size_t>()->default_value(3), "Directory scan depth")
			("min_file_size", po::value<uintmax_t>()->default_value(1), "Minimum file size")
			("file_masks", po::value<std::vector<std::string>>()->multitoken()->default_value(std::vector<std::string>{}), "Mask for files to scans")
			("block_size", po::value<size_t>()->default_value(512), "Block size in bytes")
			("hash", po::value<std::string>()->default_value("crc32"), "Hash algo crc32/md5/sha1");

		po::variables_map vm;
		po::store(parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if(vm.count("help")) {
			std::cout << desc << '\n';
		}
		else if(vm.count("include")) {
		SearchDuplicate file_dup( vm["include"].as<std::vector<std::string> >(),
								  vm["exclude"].as<std::vector<std::string> >(),
								  vm["file_masks"].as<std::vector<std::string> >(),
								  vm["block_size"].as<size_t>(),
								  vm["depth_scan"].as<size_t>() + 1,
								  vm["min_file_size"].as<uintmax_t>(),
								  vm["hash"].as<std::string>()
			);
			auto file_duplicates = file_dup.Duplicates();
			for(const auto& elem : file_duplicates) {
				std::cout << elem.first << '\n';
				for(const auto& j : elem.second) {
					std::cout << j << '\n';
				}
				std::cout << std::endl;
			}	

		}
	}
	catch(const po::error& ex) {
		std::cerr << ex.what() << '\n';
	}
}
