#include <fstream>
#include <iterator>
#include <ostream>
#include <strings.h>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <fmt/core.h>

#include "rle.hpp"

template <typename T>
void fill_vector(std::vector<T>& vec, std::ifstream& file)
{
	file.seekg(0, file.end);
	std::size_t size = file.tellg();
	file.seekg(file.beg);

	for (std::size_t i = 0; i < size/sizeof(T); i++)
	{
		T temporary_value;
		file.read((char*)&temporary_value, sizeof(T));
		vec.push_back(temporary_value);
	}
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		fmt::println(stderr, "Usage: {} INPUT OUTPUT", argv[0]);
		return 1;
	}

	std::ifstream file_in(argv[1], std::ios::binary);
	if (!file_in.is_open())
	{
		fmt::print(stderr, "Failed to open file {} for reading. Check permissions.\n", argv[1]);
		return 2;
	}

	std::vector<uint32_t> pixel_data;
	fill_vector<uint32_t>(pixel_data, file_in);	

	fmt::print(stderr, "Size {}\n", pixel_data.size());
	std::map<uint32_t, uint8_t> color_index;

	for (auto& p : pixel_data)
	{
		color_index[p];
	}

	std::size_t index = 0;
	for (auto& c : color_index)
	{
		c.second = index++;
	}
	
	std::vector<uint8_t> indexes;
	for (auto& p : pixel_data)
	{
		indexes.push_back(color_index[p]);
	}

	auto rle = rle_encode(indexes);
	
	std::ofstream file_out(argv[2]);
	if (!file_out.is_open())
	{
		fmt::print(stderr, "Could not open file {} for writing. Check permissions or available storage.\n", argv[2]);
		return 3;
	}

	std::copy(rle.begin(), rle.end(), std::ostream_iterator<uint8_t>(file_out));
	fmt::print(stdout, "File {} to file {}\n", argv[1], argv[2]);
	return 0;
}
