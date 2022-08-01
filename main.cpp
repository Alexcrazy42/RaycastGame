#include <SFML/Graphics.hpp>
#include "settings.h"
#include "Player.h"
#include "Texture.h"
#include "map.h"
#include "view.h"
#include "FPS.h"
#include <iostream>
#include <sstream>
#include <cmath>



using namespace sf;
using namespace std;



int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Game");
	view.reset(FloatRect(0, 0, WIDTH_MAP * TILE/2, HEIGHT_MAP * TILE/2));
	//window.setMouseCursorVisible(false);
	//window.setFramerateLimit(60);

	Player p(250, 250, 32.0, 32.0);
		
	
	
	Clock clock;
	Clock gameTimeClock;
	
	FPS fps;
	Font font;
	Text fpsNum;
	font.loadFromFile("CyrilicOld.TTF");
	fpsNum.setFont(font);
	fpsNum.setCharacterSize(45);
	fpsNum.setFillColor(Color::Red);
	
	
	int gameTime = 0;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		fps.update();
		
		
		ostringstream ss;
		ss << fps.getFPS();
		p.fps = fps.getFPS();
		
		fpsNum.setString(ss.str());
		
		p.sprite.setRotation(p.GetRotationDegress(window));

		fpsNum.setPosition(645, 3);
		
		
		
		p.update(time, window);
		window.setView(view);
		window.clear();

		//RenderMap(window);
		window.draw(p.sprite);
		p.Raycast(window); 
		

		window.draw(fpsNum);
		window.display();
	}
	return 0;
}