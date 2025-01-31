#pragma once
#include "keyboard-to-bool.h"
#include <math.h>


sf::Texture bot_txtr("textures/quill.png");
sf::Sprite bot(bot_txtr);
sf::Clock input_update_clock;
sf::Time cap_input_update = sf::milliseconds(50);


// stores booleans of "so-needed" events lmao
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

// stores stats that sf::sprite couldn't store
class
{
public:
			// static parameters
		// acceleration of forward or backward movement (relative to current angle)
	const float accel = 0.3f;
		// acceleration of left or right movement (relative to current angle)
	const float accel_side = accel / 2;
		// acceleration of rotation
	const int spd_rotation = 1;
		// max (speed of) rotation
	const int cap_rotation = 20;

			// dynamic parameters
		// current speed for in-game X coord
	float dx = 0.f;
		// current speed for in-game Y coord
	float dy = 0.f;
		// current angle, relative to in-game XY coords
	sf::Angle angle = sf::degrees(0);
		// current (speed of) rotation
	int rotation = 0;
		
	
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
		bot_stats.dy += -bot_stats.accel * cosf(bot_stats.angle.asRadians());
	}	
	if (getkey.s)
	{
		bot_stats.dx -= bot_stats.accel * sinf(bot_stats.angle.asRadians());
		bot_stats.dy -= -bot_stats.accel * cosf(bot_stats.angle.asRadians());
	}

	// processing of rotation
	if (getkey.a && bot_stats.rotation > -bot_stats.cap_rotation)
		bot_stats.rotation -= bot_stats.spd_rotation;
	if (getkey.d && bot_stats.rotation < bot_stats.cap_rotation)
		bot_stats.rotation += bot_stats.spd_rotation;

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
			bot_stats.dx += bot_stats.accel;
		else if (bot_stats.dx > bot_stats.accel)
			bot_stats.dx -= bot_stats.accel;
		else bot_stats.dx = 0;


		if (bot_stats.dy < -bot_stats.accel)
			bot_stats.dy += bot_stats.accel;
		else if (bot_stats.dy > bot_stats.accel)
			bot_stats.dy -= bot_stats.accel;
		else bot_stats.dy = 0;
	}
}

void bot_proc_phys()
{
	// ayy, it's empty here now.
	// you've probably guessed it right, it's currently to be done.
}


/*
					  _              __
					 | |            / _|                       
   ___ ___  _ __ ___ | |__   ___   | |_ _   _ _ __   ___ ___  (=)
  / __/ _ \| '_ ` _ \| '_ \ / _ \  |  _| | | | '_ \ / __/ __|
 | (_| (_) | | | | | | |_) | (_) | | | | |_| | | | | (__\__ \  
  \___\___/|_| |_| |_|_.__/ \___/  |_|  \__,_|_| |_|\___|___/ (=)
*/

// processing rotation, movement (and to be implemented - collision and something else idk)
void bot_processing_it_all()
{
	bot.rotate(sf::degrees(bot_stats.rotation));
	bot.move({ bot_stats.dx, bot_stats.dy });
}
																				// janky var init, for realtime in-game debug text
																				char debugtext[48];

void bot_loop()
{
	// here i implemented input throttling by timer.
	// did it in mind of debugging when CPU couldn't handle all the maths.
	// cuurrently it does... really... nothing useful.
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

	//calling other functions to complete the full processing
	bot_proc_phys();
	bot_processing_it_all();
																				// janky sprintf_s, to feed some variables to debugtext[40]
																				sprintf_s(debugtext, "e %f %f", (bot_stats.dx), bot_stats.dy);
}