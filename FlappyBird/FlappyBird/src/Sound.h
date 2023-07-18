#include <SFML/Audio.hpp>
#pragma once

class setSound 
{
public:
	sf::SoundBuffer s1, s2, s3;
	sf::Sound jump, bonus, fail;

	setSound() 
	{
		s1.loadFromFile("Sound/jump.ogg");
		s2.loadFromFile("Sound/bonus.ogg");
		s3.loadFromFile("Sound/fail.ogg");

		jump.setBuffer(s1);
		bonus.setBuffer(s2);
		fail.setBuffer(s3);
	}
};

setSound sound;