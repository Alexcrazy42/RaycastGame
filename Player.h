#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "map.h"
#include "FPS.h"
#include "Texture.h"
#include "view.h"
#include <iostream>
#include <cmath>



using namespace std;
using namespace sf;


class Player
{
public:
	float x, y, w, h, dx, dy, speed, rotation, fps, upDown;
	int dir, playerScore, health;
	bool life, sitting, esc;
	String File, numGun;
	Image image;
	Texture texture;
	Sprite sprite;

	Image wall1, wall2; 
	Texture wallTexture1, wallTexture2;
	Sprite wallSprite1, wallSprite2;
	
	Player(/*String F,*/ float X, float Y, float W, float H)
	{
		dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
		rotation = 0;
		numGun = "1";
		upDown = 0;
		
		
		
		wall1.loadFromFile("images/wall1.png");//загружаем в него файл
		wallTexture1.loadFromImage(wall1);//передаем в него объект Image (изображения)
		wallSprite1.setTexture(wallTexture1);

		wall2.loadFromFile("images/wall2.png");//загружаем в него файл
		wallTexture2.loadFromImage(wall2);//передаем в него объект Image (изображения)
		wallSprite2.setTexture(wallTexture2);


		
		w = W; h = H;
		//image.loadFromFile("images/" + File);
		//image.createMaskFromColor(Color(0, 0, 255));
		texture.loadFromImage(image);
		//sprite.setTexture(texture);
		x = X; y = Y;
		//sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setOrigin(w / 2, h / 2);

		
	}

	void update(float time, RenderWindow& window)
	{
		switch (dir)
		{
		case 0:
			dx = cos(rotation + PI / 2) * speed * time;
			dy = sin(rotation + PI / 2) * speed * time;
			break;
		case 1:
			dx = cos(rotation - PI / 2) * speed * time;
			dy = sin(rotation - PI / 2) * speed * time;
			break;
		case 2:
			dx = -cos(rotation) * speed * time;
			dy = -sin(rotation) * speed * time;
			break;
		case 3:
			dx = cos(rotation) * speed * time;
			dy = sin(rotation) * speed * time;
			break;
		}
		/*
		x += dx; 
		y += dy;
		*/
		
		sprite.setPosition(x, y);
		PlayerControl(window);
		GunControl(window);
		//CollisionWithMap(window);

		
		
		

		

	}

	float getplayercoordinateX() {
		return x;
	}

	float getplayercoordinateY() {
		return y;
	}

	void PlayerControl(RenderWindow& window)
	{

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			dir = 1; speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			dir = 0; speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			dir = 3; speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			dir = 2; speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			rotation -= 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			rotation += 0.1;
		}
		
		x += dx; 
		y += dy;
		int differenceX = Mouse::getPosition(window).x - (int)window.getSize().x / 2;
		int differenceY = Mouse::getPosition(window).y - (int)window.getSize().y / 2;
		Mouse::setPosition({ (int)window.getSize().x / 2, (int)window.getSize().y / 2 }, window);
		if (upDown > 210) upDown = 210;
		if (upDown < -300) upDown = -300;
		rotation += 0.004 * (1 / (fps + 1)) * differenceX;
		upDown -= (2.5 / (fps + 1)) * differenceY;
		
		
		
	}
	
	void GunControl(RenderWindow& window)
	{
		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			numGun = "1";
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			numGun = "2";
		}

	}

	float GetRotationDegress(RenderWindow& window)
	{
		float rotationDegrees = rotation * 180 / PI;
		return rotationDegrees;
	}

	int* Mapping(float a, float b)
	{
		int* co = new int[2];
		co[0] = int(a / TILE) * TILE;
		co[1] = int(b / TILE) * TILE;
		return co;
	}

	void Raycast(RenderWindow& window)
	{

		GameTexture gt;
		

		int xm = Mapping(x, y)[0];
		int ym = Mapping(x, y)[1];
		float curAngle = rotation - HALF_FOV;
		String numberWallX, numberWallY, numberWall;

		for (int ray = 0; ray < NUM_RAYS; ray++)
		{
			float sin_a = sin(curAngle);
			float cos_a = cos(curAngle);


			float curXH, curYV, depth_v, depth_h, depth;
			int curDx, curDy;
			float curX, curY;
			

			if (cos_a >= 0)
			{
				curX = xm + TILE;
				curDx = 1;
			}
			else
			{
				curX = xm;
				curDx = -1;
			}

			for (int i = 0; i < WIDTH; i += TILE)
			{
				depth_v = (curX - x) / cos_a;
				curYV = y + depth_v * sin_a;
				if (int(curYV / TILE) >= 0 and int(curYV / TILE) < HEIGHT_MAP and int((curX + curDx) / TILE) >= 0 and int((curX + curDx) / TILE) < WIDTH_MAP)
				{
					if (TileMap[int(curYV / TILE)][int((curX + curDx) / TILE)] != ' ')
					{
						numberWallX = TileMap[int(curYV / TILE)][int((curX + curDx) / TILE)];
						break; 
					}
				}
				curX += (curDx * TILE);
			}



			if (sin_a >= 0)
			{
				curY = ym + TILE;
				curDy = 1;
			}
			else
			{
				curY = ym;
				curDy = -1;
			}

			for (int i = 0; i < HEIGHT; i += TILE)
			{
				depth_h = (curY - y) / sin_a;
				curXH = x + depth_h * cos_a;

				if (int((curY + curDy) / TILE) >= 0 and int((curY + curDy) / TILE) < HEIGHT_MAP and int(curXH / TILE) >= 0 and int(curXH / TILE) < WIDTH_MAP)
				{
					if (TileMap[int((curY + curDy) / TILE)][int(curXH / TILE)] != ' ')
					{
						numberWallY = TileMap[int((curY + curDy) / TILE)][int(curXH / TILE)];
						break;
					}
				}
				curY += (curDy * TILE);
			}

			float offset;
			
			depth = (depth_v < depth_h) ? depth_v : depth_h;
			depth *= cos(rotation - curAngle);
			numberWall = (depth_v < depth_h) ? numberWallX : numberWallY;
			offset = (depth_v < depth_h) ? curYV : curXH;
			offset = int(offset) % TILE;
			float proj_height = PROJ_COEFF / (depth + 0.0001);


			
			float a = 0.8 - (1.6 / (1 + pow(e, 0.001 * depth)));
			a *= 255/2;
			
			/*
			VertexArray lines(Lines, 2);
			lines[0].color = Color::Red;
			lines[1].color = Color::Red;
			lines[0].position = Vector2f(x, y);
			lines[1].position = Vector2f(x + depth * cos_a, y + depth * sin_a);
			window.draw(lines);
			*/

			
			
			
			
			

			
			if (numberWall == "1")
			{
				wallSprite1.setTextureRect(IntRect(offset * TEXTURE_SCALE, 0, TEXTURE_SCALE, TEXTURE_HEIGHT));
				wallSprite1.setScale(Vector2f(0.033333334 * PIXEL_SCALE, proj_height / TEXTURE_HEIGHT));
				wallSprite1.setPosition(Vector2f(ray * SCALE, 0.5 * HEIGHT - int(proj_height / 2) + upDown));
				//wallSprite.setColor(Color(0, 0, 0, a));
				//wallSprite.createMaskFromColor(Color(0, 0, 255));
				window.draw(wallSprite1);
			}

			else if (numberWall == "2")
			{
				wallSprite2.setTextureRect(IntRect(offset * TEXTURE_SCALE, 0, TEXTURE_SCALE, TEXTURE_HEIGHT));
				wallSprite2.setScale(Vector2f(0.033333334 * PIXEL_SCALE, proj_height / TEXTURE_HEIGHT));
				wallSprite2.setPosition(Vector2f(ray * SCALE, 0.5 * HEIGHT - int(proj_height / 2) + upDown));
				window.draw(wallSprite2);
			}
			
			
			
			
			
				
				
				
				
				
				
			/*
			if (ray % 100 == 0)
			{
				RectangleShape rectangle(Vector2f(SCALE, proj_height));
				float color = 255 / (1 + pow(depth, 2) * 0.00001);
				rectangle.setFillColor(Color(255, 255, 0));
				rectangle.setPosition(Vector2f(ray* SCALE, 0.5 * HEIGHT - int(proj_height / 2) + upDown));
				window.draw(rectangle); 
			}
			*/
			
			

				
				

			curAngle += DELTA_ANGLE; 

		}
		//gt.FloorAndSky(window, upDown);
		//gt.Gun(window, numGun);
		//gt.Aim(window);
		




		/*
		float xm, ym;
		float curAngle = rotation - HALF_FOV;
		for (int i = 0; i < NUM_RAYS; i++)
		{
			float sin_a = sin(curAngle);
			float cos_a = cos(curAngle);
			for (float depth = 0; depth < MAX_DEPTH; depth+=1 )
			{
				xm = x + depth * cos_a;
				ym = y + depth * sin_a;

				if (TileMap[int(ym / TILE)][int(xm / TILE)] != ' ')
				{


					depth *= cos(rotation - curAngle);




					float proj_height = PROJ_COEFF / depth;
					RectangleShape rectangle(Vector2f(SCALE, proj_height*0.9));
					float color = 255 / (1 + pow(depth, 2) * 0.00001);
					rectangle.setFillColor(Color(color, color, color));
					rectangle.setPosition(Vector2f(i * SCALE, 0.5 * HEIGHT - int(proj_height / 2)));
					cout << upDown << endl;
					window.draw(rectangle);



					break;
				}
			}
			curAngle += DELTA_ANGLE;
			}
			*/

	}
		
		



	// коллизия недоделанная
	
	int CollisionWithMap(float X, float Y)
	{
		/*
		float cell_x = X / TILE;
		float cell_y = Y / TILE;

		for (unsigned char a = 0; a < 4; a++)
		{
			short i_x = 0;
			short i_y = 0;

			switch (a)
			{
			case 0:
			{
				i_x = static_cast<short>(floor(cell_x));
				i_y = static_cast<short>(floor(cell_y));

				break;
			}
			case 1:
			{
				i_x = static_cast<short>(ceil(cell_x));
				i_y = static_cast<short>(floor(cell_y));

				break;
			}
			case 2:
			{
				i_x = static_cast<short>(floor(cell_x));
				i_y = static_cast<short>(ceil(cell_y));

				break;
			}
			case 3:
			{
				i_x = static_cast<short>(ceil(cell_x));
				i_y = static_cast<short>(ceil(cell_y));
			}
			}

			if (0 <= i_x && 0 <= i_y && HEIGHT_MAP > i_y && WIDTH_MAP > i_x)
			{
				if (TileMap[i_y][i_x] != ' ')
				{
					return 1;
				}
			}
		}
		return 0;
		*/
	}
	
	


};