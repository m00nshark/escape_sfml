#pragma once
#include <SFML/Graphics.hpp>

//map is 80x45

namespace level
{

	class
	{
		enum class cell_type { space, wall, door, interaction, spawn, end };
		cell_type cellmap[128][128];
		unsigned int map_size[2];

		// generate cell map
		void genmap()
		{
			sf::Image cellmapper("levels/tutorial.bmp");
			map_size[1] = cellmapper.getSize().x;
			map_size[2] = cellmapper.getSize().y;

			sf::Color current_color = cellmapper.getPixel({ 1,1 });

		}



	public:
		void init()
		{
			genmap();
		}

	} tutorial;

}