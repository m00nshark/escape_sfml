/*
        a main file. all stuff related to main_window management should be put here and not anywhere else.
        (reminder for myself)
*/

#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <cmath>
#include "math.h"

#include "bot.h"
#include "keyboard-to-bool.h"

int main()
{
    // these lines are for hiding a debug console if in debug mode
    #ifdef NDEBUG
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
    #endif

    // create a main_window, next line - cap it's framerate (and with it - update rate) to 60
    sf::RenderWindow main_window(sf::VideoMode({ 1280, 720 }), "escape the void, the game", sf::Style::Default, sf::State::Windowed);
    main_window.setFramerateLimit(60);

        // init code
    bot_init();

    //init terminus font
    sf::Font f_terminus("fonts/terminus.ttf");
    // init text, currently for debug goals
    sf::Text debugger_text(f_terminus);
    debugger_text.setCharacterSize(36);
    debugger_text.setFillColor(sf::Color::White);
    debugger_text.setStyle(sf::Text::Regular);
    debugger_text.setPosition({ 10.f, 674.f });
    debugger_text.setString("d");

    // init text for movement tooltip
    sf::Text tooltip_text(f_terminus);
    tooltip_text.setCharacterSize(24);
    tooltip_text.setFillColor(sf::Color::White);
    tooltip_text.setStyle(sf::Text::Regular);
    tooltip_text.setPosition({ 10.f, 10.f });
    tooltip_text.setString
    (" W/A - acceleration \n A/D - rotation \n Q+E - stop \n F1 - show this tooltip");
    // init timer for autohiding tooltip
    sf::Clock tooltip_hide_timer;
    sf::Time tooltip_autohide_delay = sf::seconds(3);
    tooltip_hide_timer.restart();


    // main WHILE loop
    while (main_window.isOpen())
    {
        // main_window event seeker, so window closes on alt+f4
        while (const std::optional event = main_window.pollEvent())      // makes main_window alive, does event control
        {
            if (event->is<sf::Event::Closed>())
                main_window.close();
        }
        // exit on pressing ESC key, legacy of 0f0x64's PONG
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))  // seek for pressing an ESC button, close main_window if true
        {
            main_window.close();
        }

        //out-of-drawing loop code
        key_upd_full();
        bot_loop();
        // handling auto-hiding of tooltip
        if (tooltip_hide_timer.getElapsedTime() > tooltip_autohide_delay)
             tooltip_text.setFillColor(sf::Color(255, 255, 255, 0));
        else tooltip_text.setFillColor(sf::Color(255, 255, 255, 255));

        if (getkey.f1) tooltip_hide_timer.restart();


        main_window.clear(sf::Color::Black);

        // drawing loop code
        if (true)
        {
            window_size = main_window.getSize();
            main_window.draw(bot);
        }

        //debug text drawing
        debugger_text.setString(debugtext);
        
        main_window.draw(tooltip_text);
        main_window.draw(debugger_text);
        main_window.display();
    }
}
