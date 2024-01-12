//For version 1.02 of REXPaint
#pragma once
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <array>
#include <vector>


//This struct matches the order and width of data in .xp tiles.
struct RexTile
{
	//the CP437 character is mandated 4 bytes wide in the manual, likely because Kyzrati is planning ahead for things like UTF-32. so we have 1 byte character and 3 bytes padding.
	//the REXPaint manual doesn't mention endianness. so we assume everything is little endian and hope everything works out.
	uint8_t character;
	std::array<uint8_t, 3> padding; //manual padding, instead of uint32_t character, so that the alignment is tightly packed
	std::array<uint8_t, 3> fore; //in RGB
	std::array<uint8_t, 3> back; //in RGB
};

struct RexImage
{
	//Load an .xp file into a new RexFile.
	RexImage(std::string const& filename)
	{
		static_assert(sizeof(RexTile) == 10, "Number of bytes in a tile is different from sizeof(RexTile) due to alignment, which means the file read into our vector will fail");

		std::ifstream my_file(filename, std::ios::in | std::ios::binary);
		if (my_file)
		{
			my_file.read((char*)&version, sizeof(version));
			my_file.read((char*)&num_layers, sizeof(num_layers));
			if (num_layers >= 4)
				std::cerr << "warning: rexpaint input file " << filename << " has more than 4 layers, but REXPaint manual says that 4 is the max\n";
			layers.resize(num_layers); //note that this can attempt to allocate excess memory. I think that's acceptable, it will lead to a terminate signal.

			for (auto& layer : layers)
			{
				//The width and height information is repeated. according to the rexpaint manual, all layers are required to have the same dimensions.
				my_file.read((char*)&width, sizeof(width));
				my_file.read((char*)&height, sizeof(height));
				layer.resize(width * height);
				my_file.read((char*)(layer.data()), sizeof(RexTile) * width * height);
			}
			my_file.close();
		}
		else
		{
			std::cerr << "file failure: " << filename << '\n';
			abort();
		}
	}

	//Returns a pointer to a single tile specified by layer, x coordinate, y coordinate.
	//0,0 is the top-left corner.
	inline RexTile* getTile(int layer, int x, int y) { return &layers.at(layer).at(y + (x * height)); };

	//Returns a pointer to a single tile specified by layer and the index into the array.
	//Useful for iterating through a whole layer in one go for coordinate-nonspecific tasks.
	inline RexTile* getTile(int layer, int index) { return &layers.at(layer).at(index); };

	uint32_t width, height, num_layers; //image properties. read-only please.
	std::vector<std::vector<RexTile>> layers; //layers[0] is the first layer.
private:
	uint32_t version; //nobody cares about the version, so it's private

	RexImage(); //Forbid default construction.
};
