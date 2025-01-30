#pragma once
#include "keyboard-to-bool.h"
#include "math.h"

sf::Texture bot_txtr("textures/quill.png");
sf::Sprite bot(bot_txtr);

class
{
public:
	bool a_i = false;
	bool d_i = false;
	bool a_o = false;
	bool d_o = false;
	bool u_turn = false;
	bool input_upd = false;
} bot_event_processed;

sf::Clock input_update_clock;
sf::Time cap_input_update = sf::milliseconds(10);

class
{
public:
	float accel = 0.3f;
	float accel_side = accel / 2;
	float dx = 0.f;
	float dy = 0.f;
	int rotation = 0.f;

	float cap_speed = 15.f;
	floar decel_proc = 0.
	float spd_rotation = 1.f;
	int cap_rotation = 20;

	float health = 1;
	float charge = 1;
	sf::Angle angle = sf::degrees(5);
} bot_stats;





void bot_init()
{
	input_update_clock.restart();
	bot.setOrigin({ 12.f, 12.f });
	bot.setPosition({ 640.f, 360.f });
}

void bot_processing_input()
{
	bot_stats.angle = bot.getRotation();
	if (getkey.w)
	{
		bot_stats.dx += bot_stats.accel * sinf(bot_stats.angle.asRadians());
		bot_stats.dy += -bot_stats.accel * cosf(bot_stats.angle.asRadians());
	}	
	if (getkey.s)
	{
		bot_stats.dx -= bot_stats.accel * sinf(bot_stats.angle.asRadians());
		bot_stats.dy -= -bot_stats.accel * cosf(bot_stats.angle.asRadians());
	}

	if (getkey.q && getkey.e)
	{
		if(bot_stats.dx > )
	}

	if (getkey.a && bot_stats.rotation > -bot_stats.cap_rotation)
		bot_stats.rotation -= bot_stats.spd_rotation;
	if (getkey.d && bot_stats.rotation < bot_stats.cap_rotation)
		bot_stats.rotation += bot_stats.spd_rotation;

	if (!getkey.a && !getkey.d && !(bot_stats.rotation == 0))
	{
		if (bot_stats.rotation > bot_stats.spd_rotation - 0.003f)
			bot_stats.rotation -= bot_stats.spd_rotation;
		else if (bot_stats.rotation < -bot_stats.spd_rotation + 0.003f)
				 bot_stats.rotation += bot_stats.spd_rotation;
	}
}

void bot_processing_it_all()
{
	
	bot.rotate(sf::degrees(bot_stats.rotation));
	bot.move({ bot_stats.dx, bot_stats.dy });
}

void bot_proc_phys()
{

}



																				char debugtext[48];

void bot_loop()
{
	if (bot_event_processed.input_upd) bot_event_processed.input_upd = false;
	if (input_update_clock.getElapsedTime() > cap_input_update)
	{
		if (!bot_event_processed.input_upd)
		{
			bot_processing_input();
			bot_event_processed.input_upd = true;
			input_update_clock.restart();
		}
		else
		{
			bot_processing_input();
			input_update_clock.restart();
		}
	}

	bot_processing_it_all();
	sprintf_s(debugtext, "e %.3f %.3f", (bot_stats.dx), bot_stats.angle.asRadians());
}