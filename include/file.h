#pragma once
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>

#include "hash.h"
namespace fs = boost::filesystem;
struct HashBlock
{
	digest data;
	bool operator==(const HashBlock& other) const;
	bool operator!=(const HashBlock& other) const;
};

class File
{
public:
	bool in_result = false;
	const size_t block_count;
	File(fs::path path, uintmax_t size, uintmax_t hash_blocksize, IHasher* hasher) //
		: path(path), filesize(size), blocksize(hash_blocksize), hasher(hasher),
		block_count((size + hash_blocksize - 1) / hash_blocksize) {};
	bool operator==(const File& other) const;
	size_t get_hash_data_Size() const;
	uintmax_t get_file_size() const;
	fs::path get_path() const;
	void open_handle();
	void close_handle();
	std::unique_ptr<char[]> get_next_block();
	void calc_next_hash();
	HashBlock calc_hash_block(size_t addr);
	HashBlock get_hash_block(size_t addr);
	bool equal_hash_file(File& other);
private:
	fs::path path;
	uintmax_t filesize;
	std::vector<HashBlock> hash_data;
	uintmax_t blocksize;
	IHasher* hasher;
	std::unique_ptr<std::ifstream> file_handle;
};
