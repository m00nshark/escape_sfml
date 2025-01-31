#pragma once
#include "SFML/Window.hpp"

/*
this header so stupidly plain, should i even tell what does it do?
*/

class
{
public:
	bool a;

	bool c;
	bool d;
	bool e;
	bool f;

	bool q;
	bool r;
	bool s;

	bool v;
	bool w;
	bool x;

	bool z;
} getkey;

void key_upd_full()
{
	getkey.a = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);

	getkey.c = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C);
	getkey.d = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	getkey.e = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
	getkey.f = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F);

	getkey.q = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
	getkey.r = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R);
	getkey.s = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);

	getkey.v = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V);
	getkey.w = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	getkey.x = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X);

	getkey.z = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
}