#pragma once
#include <SFML\Graphics.hpp>
using namespace sf; 

View view; 

void getplayercoordinateforview(float x, float y) 
{ 

	float tempX = x; float tempY = y;
	view.setCenter(tempX, tempY);
}

