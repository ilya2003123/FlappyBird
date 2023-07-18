#pragma once
#include <SFML/Graphics.hpp>
#include "Mvar.h"

class Player 
{
public:
	float dx, dy;
	sf::FloatRect rect;
	bool onGround;
	sf::Sprite sprite;
	float curFrame;

	Player(sf::Texture& image) 
	{
		sprite.setTexture(image);
		sprite.setTextureRect(sf::IntRect(0, 0, 38, 25));

		rect.left = 125;
		rect.top = 100;

		dx = dy = 0;
		curFrame = 0;
	}

	void update(float time) 
	{
		rect.left += dx * time;

		if (!onGround && (play || over))
			dy = dy + 0.0005 * time;

		rect.top += dy * time;

		onGround = false;

		if (rect.top > 480) 
		{
			rect.top = 480;
			dy = 0;

			onGround = true;
		}

		if (!over) 
		{
			curFrame += 0.005 * time;
			if (curFrame > 3)
				curFrame -= 3;

			sprite.setTextureRect(sf::IntRect(38 * int(curFrame), 0, 38, 25));
		}

		sprite.setPosition(rect.left, rect.top);

		dx = 0;
	}
};