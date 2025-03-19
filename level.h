#pragma once
#include <SFML/Graphics.hpp>
#include "bot.h"
#include <cmath>

namespace level
{
	

		// initialize textures & sprites for drawing sprited map
		sf::Texture t_space("textures/space.bmp");
			sf::Sprite space(t_space);
		sf::Texture t_floor("textures/floor.bmp");
			sf::Sprite floor(t_floor);
		sf::Texture t_wall("textures/wall.bmp");
			sf::Sprite wall(t_wall);
		sf::Texture t_door("textures/door.bmp");
			sf::Sprite door(t_door);
		sf::Texture t_interaction("textures/interaction.bmp");
			sf::Sprite interaction(t_interaction);
		sf::Texture txtr_error("textures/error.bmp");
			sf::Sprite sprite_error(txtr_error);

		sf::Sprite* sprite_atlas[] = { &space , &floor , &wall , &door , &interaction , &interaction, &floor, &sprite_error};
		// initialize a spawnpoint variable for main bot
		sf::Vector2f spawnpoint(128.f, 128.f);

		// enumerate types of cells
		enum class cell_type { space, floor, wall, door, interaction, spawn, end, sprite_error };
		// set a size for map
		const int cellmap_size_x = 100;
		const int cellmap_size_y = 50;
		// array that stores types of cells in map
		cell_type cellmap[cellmap_size_x][cellmap_size_y];
		// for unfixed sizes of mapper-bmps, create an array that stores it's size
		unsigned int map_size[2];
		// define cell size, in pixels. needed for correct cell display
		int cell_size = 24;

	class
	{

		// generate cell map
		void genmap()
		{
			// load an mapper-bmp
			sf::Image cellmapper("levels/tutorial/map.bmp");
			// loading mapper's size
			map_size[0] = cellmapper.getSize().x;
			map_size[1] = cellmapper.getSize().y;

			// read mapper and get bitches... hahaha no, get the types of the cells
			for (unsigned int m = 0; m < map_size[0]; m++)
			{
				for (unsigned int n = 0; n < map_size[1]; n++)
				{
					switch (  cellmapper.getPixel({m,n}).toInteger()  )
					{
					case 0xffffffff: cellmap[m][n] = cell_type::space;			break;
					case 0x7f7f7fff: cellmap[m][n] = cell_type::floor;			break;
					case 0x000000ff: cellmap[m][n] = cell_type::wall;			break;
					case 0xFF0000FF: cellmap[m][n] = cell_type::door;			break;
					case 0x00ff00ff: cellmap[m][n] = cell_type::interaction;	break;
					case 0x007f00ff: cellmap[m][n] = cell_type::end;			break;
					case 0x0000ffff:
						{
							cellmap[m][n] = cell_type::spawn;
							spawnpoint = sf::Vector2f(
								{
									m * cell_size * 1.f + cell_size * 0.5f ,
									n * cell_size * 1.f + cell_size * 0.5f
								}
							);
							break;
						}
						
					default: cellmap[m][n] = cell_type::sprite_error; break;
					}

				}
			}

		}

		// smooth the cunt out of these textures (they still cut your eye
		// like paper cuts that place between your fingers lol)
		void set_smooth()
		{
			t_space.setSmooth(true);
			t_floor.setSmooth(true);
			t_wall.setSmooth(true);
			t_door.setSmooth(true);
			t_interaction.setSmooth(true);
		}

	public:	

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

		sf::Vector2f spawnpoint;

		void init()
		{
			genmap();
			set_smooth();
		}

		int clamp(int x, int a, int b)
		{	
			return MAX(MIN(x, b), a);
		}

		// map drawer, so you move not in the void, but somewhere
		void drawmap(sf::RenderWindow &wndw)
		{
			for (unsigned int m = 0; m <= map_size[0]; m++)
			{
				for (unsigned int n = 0; n <= map_size[1]; n++)
				{
					sf::Vector2f pos = { (cell_size * m) * 1.f, (cell_size * n) * 1.f };
					auto spriteID = clamp((int)cellmap[m][n],0,7);
					sprite_atlas[spriteID]->setPosition(pos);
					wndw.draw(*sprite_atlas[spriteID]);
				}
			}
		}

		sf::Vector2u col_curr_pos;
		sf::Vector2u col_prev_pos;

		void collider()
		{
			col_curr_pos = {(UINT)(bot.getPosition().x / cell_size) , (UINT)(bot.getPosition().y / cell_size)};

		}
	} tutorial;

}
