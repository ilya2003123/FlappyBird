#include <SFML/Graphics.hpp>

int main()
{
	srand(time(NULL));
	const float FPS = 60.0f;

	int x = 100, y = 150;
	int xUpPipe = 838, yUpPipe = 127, xDownPipe = 700, yDownPipe = 375;
	float fallSpeed = 0;
	int type = 0;

	int xPipe;
	float speedPipe = 2.5f;
	float distanceBetweenPipe = 0;
	long long score = 0;
	bool isNewGameTimeStart = false;
	sf::RenderWindow window(sf::VideoMode(700, 504), "FlappyBird");
	window.setFramerateLimit(FPS);

	sf::Font font;
	font.loadFromFile("score.ttf");
	sf::Text text;
	text.setFont(font);
	text.setPosition(10, 10);
	text.setFillColor(sf::Color::Red);

	sf::Texture bird_t;
	bird_t.loadFromFile("duck.png");
	sf::Texture backGround_t;
	backGround_t.loadFromFile("bg.png");
	sf::Texture pipe_t;
	pipe_t.loadFromFile("pipe.png");

	sf::Sprite bird_s;
	sf::Sprite backGroundStart_s;
	sf::Sprite backGroundEnd_s;
	sf::Sprite pipeUp_s;
	sf::Sprite pipeDown_s;

	pipeUp_s.setTexture(pipe_t);
	pipeDown_s.setTexture(pipe_t);
	pipeDown_s.setRotation(180);
	pipeDown_s.setPosition(xDownPipe, yDownPipe);
	pipeUp_s.setPosition(xUpPipe, yUpPipe);

	backGroundStart_s.setTexture(backGround_t);
	backGroundStart_s.setPosition(0, 0);
	backGroundStart_s.setScale(2.5f, 3);
	backGroundEnd_s.setTexture(backGround_t);
	backGroundEnd_s.setPosition(700, 0);
	backGroundEnd_s.setScale(2.5f, 3);

	bird_s.setTexture(bird_t);
	bird_s.setPosition(x, y);
	bird_s.setScale(0.4f, 0.4f);

	distanceBetweenPipe -= 10;

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					fallSpeed = -7.5f;
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					isNewGameTimeStart = false;
					bird_s.setPosition(x, y);
					pipeDown_s.setPosition(xDownPipe, yDownPipe);
					pipeUp_s.setPosition(xUpPipe, yUpPipe);
					backGroundStart_s.setPosition(0, 0);
					backGroundEnd_s.setPosition(700, 0);
				}
			}
		}

		type = rand() % 3 + 1;
		if (type == 1)
		{
			yDownPipe = 202 - distanceBetweenPipe;
			yUpPipe = 440 + distanceBetweenPipe;
		}
		if (type == 2)
		{
			yDownPipe = 127 - distanceBetweenPipe;
			yUpPipe = 375 + distanceBetweenPipe;
		}
		if (type == 3)
		{
			yDownPipe = 62 - distanceBetweenPipe;
			yUpPipe = 300 + distanceBetweenPipe;
		}
		fallSpeed += 0.5f;
		bird_s.move(0, fallSpeed);
		bird_s.setRotation(static_cast<int>(fallSpeed - 2.5f) % 90);
		pipeDown_s.move(speedPipe * -1, 0);
		pipeUp_s.move(speedPipe * -1, 0);
		speedPipe += 0.004f;
		backGroundStart_s.move(-0.4, 0);
		backGroundEnd_s.move(-0.4, 0);

		if (backGroundStart_s.getPosition().x <= -700)
		{
			backGroundStart_s.setPosition(700, 0);
		}
		if (backGroundEnd_s.getPosition().x <= -700)
		{
			backGroundEnd_s.setPosition(700, 0);
		}
		xPipe = pipeUp_s.getPosition().x;
		if (xPipe < 0)
		{
			pipeDown_s.setPosition(xDownPipe, yDownPipe);
			pipeUp_s.setPosition(xUpPipe, yUpPipe);
			score++;
		}

		if ((bird_s.getPosition().y <= 0) || (bird_s.getPosition().y >= 432) || (isNewGameTimeStart)
			|| ((bird_s.getGlobalBounds().intersects(pipeDown_s.getGlobalBounds()))
				|| (bird_s.getGlobalBounds().intersects(pipeUp_s.getGlobalBounds()))))
		{
			score = 0;
			speedPipe = 2.5f;
			window.clear();
			backGroundStart_s.setPosition(0, 0);
			window.draw(backGroundStart_s);
			isNewGameTimeStart = true;
			window.display();
		}
		else
		{
			text.setString("Score" + std::to_string(score));
			window.clear();
			window.draw(backGroundEnd_s);
			window.draw(backGroundStart_s);
			window.draw(pipeDown_s);
			window.draw(pipeUp_s);
			window.draw(bird_s);
			window.draw(text);
			window.display();

		}
	}

	return 0;
}