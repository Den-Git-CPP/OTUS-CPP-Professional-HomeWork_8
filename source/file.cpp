#include "file.h"

namespace fs = boost::filesystem;

bool HashBlock::operator==(const HashBlock& other) const {
	return data == other.data;
}
bool HashBlock::operator!=(const HashBlock& other) const {
	return !(*this == other);
}

bool File::operator==(const File& other) const {
	return fs::equivalent(path, other.path);
}

size_t File::get_hash_data_Size() const {
	return hash_data.size();
}

uintmax_t File::get_file_size() const {
	return filesize;
}

fs::path File::get_path() const {
	return path;
}

void File::open_handle() {
	if(!file_handle) {
		file_handle = std::make_unique<std::ifstream>(get_path().string());
		file_handle.get()->seekg(hash_data.size() * blocksize);
	}
}

void File::close_handle() {
	if(file_handle != nullptr) {
		file_handle->close();
		delete file_handle.release();
	}
}

std::unique_ptr<char[]> File::get_next_block() {
	open_handle();
	auto buffer = std::make_unique<char[]>(blocksize);
	file_handle->read(buffer.get(), blocksize);
	return buffer;
}


void File::calc_next_hash() {
	hash_data.emplace_back(HashBlock{hasher->Hash(get_next_block().get(), blocksize)});
}

HashBlock File::calc_hash_block(size_t addr) {
	while(hash_data.size() <= addr) {
		calc_next_hash();
	}
	return hash_data.back();
}


HashBlock File::get_hash_block(size_t addr) {
	if(addr >= block_count)
		throw;
	if(addr < hash_data.size())
		return hash_data[addr];
	else
		return calc_hash_block(addr);
}

bool File::equal_hash_file(File& other) {
	if(this->get_file_size() != other.get_file_size())
		return false;
	for(size_t i = 0; i < block_count; ++i) {
		if(get_hash_block(i) != other.get_hash_block(i)) {
			close_handle();
			other.close_handle();
			return false;
		}
	}
	close_handle();
	other.close_handle();
	return true;
}

namespace std
{
	template <>
	struct hash<File>
	{
		size_t operator()(const File& obj) const {
			return hash<string>()(obj.get_path().string());
		}
	};
}
