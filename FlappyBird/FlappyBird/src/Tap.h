#pragma once
#include <SFML/Graphics.hpp>

class Tap 
{
public:
	sf::Sprite sprite;
	bool vid;
	int time;

	Tap(sf::Texture& image) 
	{
		sprite.setTexture(image);
		sprite.setPosition(120, 200);

		vid = true;
		time = 2000;
	}

	void update() 
	{
		time--;

		if (time < 1000) 
		{

			vid = false;

			if (time == 0) 
			{
				time = 2000;
				vid = true;
			}
		}
	}
};