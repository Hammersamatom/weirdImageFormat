#include <vector>
#include <cstdint>
#include <fmt/core.h>

enum {
	SINGLE_BYTE_MAX = 1 << 3,
	DOUBLE_BYTE_MAX = 1 << 11
};

void encode_bytes(std::vector<uint8_t>& in, uint8_t character, uint32_t count)
{
	uint8_t long_run = (count >= SINGLE_BYTE_MAX && count < DOUBLE_BYTE_MAX) ? 0x80 : 0x00;
	in.push_back(long_run | ((count & 0b111) << 4) | character);
	if (long_run) in.push_back(count >> 3);
}

std::vector<uint8_t> rle_encode(const std::vector<uint8_t>& input_data)
{
	std::vector<uint8_t> output_data;

	uint8_t current_character = input_data[0];
	uint32_t current_count = 1;	
	for (std::size_t cur = 1; cur < input_data.size(); cur++)
	{
		if (current_character != input_data[cur])
		{
			encode_bytes(output_data, current_character, current_count);
			current_character = input_data[cur];
			current_count = 1;
		}
		else
		{
			current_count++;
		}
	}

	encode_bytes(output_data, current_character, current_count);

	return output_data;
}

std::vector<uint8_t> rle_decode(const std::vector<uint8_t>& input_data)
{
    std::vector<uint8_t> output_data;

    for (std::size_t i = 0; i < input_data.size(); i++)
    {
        bool long_run = 0x80 & input_data[i];
        uint8_t index = input_data[i] & 0x0F;
        uint32_t count = (input_data[i] & 0x70) >> 4;
        if (long_run) count |= (uint32_t)input_data[++i] << 3;

        for (std::size_t j = 0; j < count; j++)
        {
            output_data.push_back(index);
        }
    }

    return output_data;
}
