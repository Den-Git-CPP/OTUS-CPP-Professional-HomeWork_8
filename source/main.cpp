
#include <boost/program_options.hpp>
#include <exception>
#include <iostream>

namespace std {
	std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& vec) {
		for (const auto& item : vec) {
			os << item << " ";
		}
		return os;
	}
}

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
	try
	{
		po::options_description desc {"Options"};
		desc.add_options()
			("help,h", "Help screen")
			("include_dir,I", po::value<std::vector<std::string>>()->multitoken(), "Include directories to scan")
			("exclude_dir,E", po::value<std::vector<std::string>>()->multitoken()->default_value(std::vector<std::string>{}), "Exclude directories to exclude")
			("depth,D", po::value<size_t>()->default_value(2), "Depth to scan")
			("min_file_size,S", po::value<uintmax_t>()->default_value(1), "Minimum file size")
			("hash,H", po::value<std::string>()->default_value("crc32"), "Hash algo crc32/md5/sha1")
			("file_masks", po::value<std::vector<std::string>>()->multitoken()->default_value(std::vector<std::string>{}), "Mask for files to scans")
			("block_size", po::value<size_t>()->default_value(512), "Block size in bytes");
		po::variables_map vm;
		po::store(parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << '\n';
		}
		else if (vm.count("include_dir"))
		{
		
		}
	}
	catch (const po::error& ex)
	{
		std::cerr << ex.what() << '\n';
	}
}
