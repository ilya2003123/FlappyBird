#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Tap.h"
#include "Pipe.h"
#include "Score.h"
#include "Sound.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(288, 512), "Flappy Bird!");

	sf::Texture f;
	f.loadFromFile("Paint/background.png");
	sf::Sprite fon(f);

	sf::Texture Picture;
	Picture.loadFromFile("Paint/player.png");
	Player p(Picture);

	sf::Texture tp;
	tp.loadFromFile("Paint/tap.png");
	Tap tap(tp);

	sf::Texture pi;
	pi.loadFromFile("Paint/pipe.png");
	Pipe pipe(pi);

	sf::Texture sc;
	sc.loadFromFile("Paint/score.png");
	Score score(sc);

	sf::Texture go;
	go.loadFromFile("Paint/gameover.png");
	sf::Sprite gameover(go);
	gameover.setPosition(30, 200);

	sf::Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left) 
				{
					if (start) 
					{
						start = false;
						play = true;
					}

					if (play) 
					{
						p.dy = -0.2;

						sound.jump.play();
					}
				}
		}

		if (play) 
		{
			if (p.rect.left > 10)
				p.dx = -0.2;
			else
				p.dx = 0;

			pipe.dx = -0.05;

			if (pipe.rect.left < 0 && score.add) 
			{
				score.c++;

				score.add = false;

				sound.bonus.play();
			}
			else if (pipe.rect.left > 200)
				score.add = true;

			for (int i = 0; i < 2; i++)
				if (p.sprite.getGlobalBounds().intersects(pipe.sprite[i].getGlobalBounds()) || p.onGround) 
				{
					play = false;
					over = true;

					sound.fail.play();
				}
		}

		p.update(time);
		if (start)
			tap.update();

		pipe.update();
		score.update();
		window.clear(sf::Color::White);
		window.draw(fon);
		window.draw(p.sprite);
		if (tap.vid && start)
			window.draw(tap.sprite);
		for (int i = 0; i < 2; i++)
			window.draw(pipe.sprite[i]);
		for (int i = 0; i < 3; i++)
			if (score.vid[i])
				window.draw(score.sec[i]);
		if (over)
			window.draw(gameover);
		window.display();
	}

	return 0;
}