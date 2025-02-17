#pragma once
#include "keyboard-to-bool.h"
#include <math.h>

// some necessary variables. i think they talk for themselves
// so i don't need to describe every of them with honour and fashion
sf::Texture bot_txtr("textures/quill.png");
sf::Sprite bot(bot_txtr);
sf::Clock input_update_clock;
sf::Time cap_input_update = sf::milliseconds(50);
sf::Vector2u window_size;

// stores booleans of "so-needed" events lmao
class
{
public:
	bool a_i = false;
	bool d_i = false;
	bool a_o = false;
	bool d_o = false;
	bool u_turn = false;
} bot_event_processed;

// stores stats that sf::sprite couldn't store
class
{
public:
			// static parameters
		// acceleration of forward or backward movement (relative to current angle)
	const float accel = 0.3f;
		// acceleration of left or right movement (relative to current angle)
	const float accel_side = accel / 2;
		// value for q+e decelerator, imo it should be overpowered a little
	const float decel = accel * 2;
		// acceleration of rotation
	const int spd_rotation = 1;
		// max (speed of) rotation
	const int cap_rotation = 20;
		// bounce acceleration (should be multiplied on)
	const float bounce_accel = -0.5;

			// dynamic parameters
		// current speed for in-game X coord
	float dx = 0.f;
		// current speed for in-game Y coord
	float dy = 0.f;
		// current angle, relative to in-game XY coords
	sf::Angle angle = sf::degrees(0);
		// current (speed of) rotation as degrees
	float rotation = 0;
	
} bot_stats;



/*
   __                            _                       _   _
  / _|                          | |                     | | | |
 | |_ _   _ _ __   ___ ___    __| | _____      ___ __   | |_| |__   ___ _ __ ___
 |  _| | | | '_ \ / __/ __|  / _` |/ _ \ \ /\ / / '_ \  | __| '_ \ / _ \ '__/ _ \
 | | | |_| | | | | (__\__ \ | (_| | (_) \ V  V /| | | | | |_| | | |  __/ | |  __/
 |_|  \__,_|_| |_|\___|___/  \__,_|\___/ \_/\_/ |_| |_|  \__|_| |_|\___|_|  \___|
*/


// initialization. starts the input-update clock, sets center-point and position.
void bot_init()
{
	input_update_clock.restart();
	bot.setOrigin({ 12.f, 12.f });
	bot.setPosition({ 640.f, 360.f });
}

// processing input, in result - modifying bot_stats parameters (speed for X&Y, rotation)
void bot_processing_input()
{
	bot_stats.angle = bot.getRotation();

	// processing of forwards or backwards movement
	if (getkey.w)
	{
		bot_stats.dx += bot_stats.accel * sinf(bot_stats.angle.asRadians());
		bot_stats.dy -= bot_stats.accel * cosf(bot_stats.angle.asRadians());
	}	
	if (getkey.s)
	{
		bot_stats.dx -= bot_stats.accel * sinf(bot_stats.angle.asRadians());
		bot_stats.dy += bot_stats.accel * cosf(bot_stats.angle.asRadians());
	}

	// processing side movement
	if (getkey.e && !getkey.q)
	{
		bot_stats.dx += bot_stats.accel_side * sinf(bot_stats.angle.asRadians() + 1.5708f);
		bot_stats.dy -= bot_stats.accel_side * cosf(bot_stats.angle.asRadians() + 1.5708f);
	}
	if (getkey.q && !getkey.e)
	{
		bot_stats.dx -= bot_stats.accel_side * sinf(bot_stats.angle.asRadians() + 1.5708f);
		bot_stats.dy += bot_stats.accel_side * cosf(bot_stats.angle.asRadians() + 1.5708f);
	}

	// processing of rotation
	if (getkey.a && !getkey.d && bot_stats.rotation > -bot_stats.cap_rotation)
		bot_stats.rotation -= bot_stats.spd_rotation;
	if (getkey.d && !getkey.a && bot_stats.rotation < bot_stats.cap_rotation)
		bot_stats.rotation += bot_stats.spd_rotation;
	
	if (getkey.a && getkey.d && !bot_event_processed.u_turn)
	{
		bot.rotate(sf::degrees(180));
		bot_event_processed.u_turn = true;
	}
	if (!getkey.a && !getkey.d && bot_event_processed.u_turn)
		bot_event_processed.u_turn = false;

	if (!getkey.a && !getkey.d && !(bot_stats.rotation == 0))
	{
		if (bot_stats.rotation > bot_stats.spd_rotation - 2)
			bot_stats.rotation -= bot_stats.spd_rotation;
		else if (bot_stats.rotation < -bot_stats.spd_rotation + 2)
			bot_stats.rotation += bot_stats.spd_rotation;
	}

	// CURRENT SEGMENT OF CODE DOWN HERE IS GOING TO BE REMADE FOR BETTER PHYSIX.
	// automatic processing of full deceleration and stop
	if (getkey.q && getkey.e)
	{
		if (bot_stats.dx < -bot_stats.accel)
			bot_stats.dx += bot_stats.decel;
		else if (bot_stats.dx > bot_stats.accel)
			bot_stats.dx -= bot_stats.decel;
		else bot_stats.dx = 0;

		if (bot_stats.dy < -bot_stats.accel)
			bot_stats.dy += bot_stats.decel;
		else if (bot_stats.dy > bot_stats.accel)
			bot_stats.dy -= bot_stats.decel;
		else bot_stats.dy = 0;
	}
}

void bot_proc_phys()
{
	
	// getting current position of bot
	sf::Vector2f pos = bot.getPosition();

	// TODO - TO BE REDONE WHEN LEVEL IS MADE (CURRENTLY IT'S BOUNCING INSIDE A WINDOW)
	// TODO - CONSIDER BOT'S SIZE ! !
	// comparing if it's out of legal playing bounds
	
}


/*
					  _              __
					 | |            / _|                       
   ___ ___  _ __ ___ | |__   ___   | |_ _   _ _ __   ___ ___  (=)
  / __/ _ \| '_ ` _ \| '_ \ / _ \  |  _| | | | '_ \ / __/ __|
 | (_| (_) | | | | | | |_) | (_) | | | | |_| | | | | (__\__ \  
  \___\___/|_| |_| |_|_.__/ \___/  |_|  \__,_|_| |_|\___|___/ (=)
*/

// processing rotation, movement and physics (collision)
void bot_processing_movement()
{
	bot.rotate(sf::degrees(bot_stats.rotation));
	bot.move({ bot_stats.dx, bot_stats.dy });
	bot_proc_phys();
}
																				// janky var init, for realtime in-game debug text
																				char debugtext[48];
																				sf::Color dbgcolor = sf::Color(255, 0, 0, 255);
																				uint32_t dbgval = 0xFF00FFFFAA;

void bot_loop()
{
	// here i implemented input throttling by timer
	if (input_update_clock.getElapsedTime() > cap_input_update)
	{
		bot_processing_input();
		input_update_clock.restart();
	}

	//calling other functions to complete the full processing
		
	bot_processing_movement();

																				// janky sprintf_s, to feed some variables to debugtext[40]
																				sf::Vector2f pos = bot.getPosition();
																				sprintf_s(debugtext, "o %08X %08X", dbgcolor.toInteger(), dbgval);
}