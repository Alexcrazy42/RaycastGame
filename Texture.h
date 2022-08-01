#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "map.h"
#include "view.h"
#include <iostream>
#include <cmath>
#include <string>


class GameTexture
{
public:
	
	void FloorAndSky(RenderWindow & window, double upDown)
	{
		RectangleShape sky(Vector2f(WIDTH, HEIGHT / 2 + upDown));
		sky.setFillColor(Color(135, 206, 250));
		sky.setPosition(Vector2f(0, 0));
		window.draw(sky);

		RectangleShape floor(Vector2f(WIDTH, HEIGHT / 2 - upDown));
		floor.setFillColor(Color(255, 250, 205));
		floor.setPosition(Vector2f(0, HEIGHT / 2 + upDown));
		window.draw(floor);
	}

	void Gun(RenderWindow& window, String number)
	{
		Image gun;
		String a = "images/gun";
		String b = number + ".png";
		String nameFile = a + b;
		gun.loadFromFile(nameFile);
		
		

		Texture guntexture;
		guntexture.loadFromImage(gun);
		Sprite gunSprite;
		gunSprite.setTexture(guntexture);
		gunSprite.setPosition(400, 290);
		window.draw(gunSprite);
		
	}

	void Aim(RenderWindow& window)
	{

		Image aim;
		aim.loadFromFile("images/aim.png");



		Texture aimtexture;
		aimtexture.loadFromImage(aim);
		Sprite aimSprite;
		aimSprite.setTexture(aimtexture); 
		aimSprite.setOrigin(25, 25); 
		aimSprite.setScale(0.4, 0.4);
		//std::cout << (int)window.getSize().x / 2 << " " << (int)window.getSize().y / 2 << std::endl;
		aimSprite.setPosition(344, 225);
		
		
		window.draw(aimSprite);

	}
};