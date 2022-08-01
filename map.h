#pragma once
#include <SFML\Graphics.hpp>
#include "settings.h"
const int HEIGHT_MAP = 28;
const int WIDTH_MAP = 43;

using namespace sf; 
	

String TileMap[HEIGHT_MAP] = {
	"1111111111111111111111111111111111111111111",
	"1       1       1           1     1       1",
	"1       1       1           1     1       1",
	"1       1       11111   11111     1       1",
	"1       1                         1       1",
	"11111        111             111      11111",
	"1            111     2222    111          1",
	"1                    2222                 1",
	"11111      2222             1111      11111",
	"1          2222             1111          1",
	"1          2222             1111          1",
	"1          2222             1111          1",
	"1                                         1",
	"1                   2222                  1",
	"1111111             2222          11111111",
	"1          1111             2222          1",
	"1          1111             2222          1",
	"1          1111             2222          1",
	"1          1111             2222          1",
	"1                                         1",
	"11111               2222              11111",
	"1           222     2222     22           1",
	"1           222              22           1",
	"1       1                         1       1",
	"1       1       11111   11111     1       1",
	"1       1       1           1     1       1",
	"1       1       1           1     1       1",
	"1111111111111111111111111111111111111111111",
};


void RenderMap(RenderWindow& window)
{
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			
			
			if (TileMap[i][j] != ' ')
			{
				s_map.setTextureRect(IntRect(0, 0, 32, 32));
			}
			else
			{
				s_map.setTextureRect(IntRect(193, 0, 32, 32));
			}
			
			s_map.setPosition(j * TILE, i * TILE);
			window.draw(s_map);
		}
}
