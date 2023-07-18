#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Mvar.h"

class Pipe
{
public:
	sf::Sprite sprite[2];
	int y;
	float dx;
	sf::FloatRect rect;

	Pipe(sf::Texture& image)
	{
		for (int i = 0; i < 2; i++)
			sprite[i].setTexture(image);

		sprite[1].setTextureRect(sf::IntRect(0, 415, 45, -415));

		dx = 0;
		Coordinates();
	}

	void update()
	{
		if (play)
			rect.left += dx;

		if (rect.left < -50)
			Coordinates();

		for (int i = 0; i < 2; i++)
			sprite[i].setPosition(rect.left, rect.top - 500 * i);
	}

	void Coordinates()
	{
		srand(time(0));

		y = rand() % 6;

		rect.left = 288;
		//rect.left = 200;
		rect.top = 100 + 50 * y;
	}
};
