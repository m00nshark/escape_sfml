/*
        a main file. all sturr related to main_window mgmt should be put here and not anywhere else.
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

int main()
{
    // these lines are for hiding a debug console if in debug mode
    #ifdef NDEBUG
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
    #endif


    // create a main_window
    sf::RenderWindow main_window(sf::VideoMode({ 1280, 720 }), "escape the void, the game", sf::Style::Default, sf::State::Windowed);
    main_window.setFramerateLimit(60);

    // init code. that if(true) is here for my own convenience
    if (true)
    {
        bot_init();
    }

    // init text&font, currently for debug goals
    sf::Font f_terminus("fonts/terminus.ttf");
    sf::Text debugger_text(f_terminus);
    debugger_text.setCharacterSize(36);
    debugger_text.setFillColor(sf::Color::White);
    debugger_text.setStyle(sf::Text::Regular);
    debugger_text.setPosition({ 10.f, 674.f });
    debugger_text.setString("d");




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



        //out-of-drawing loop code. that if(true) is here for my own convenience
        if (true)
        {
            key_upd_full();
            bot_loop();
        }



        main_window.clear(sf::Color::Black);

        // drawing loop code
        if (true)
        {
            main_window.draw(bot);
        }

        //debug text drawing
        debugger_text.setString(debugtext);
        
        main_window.draw(debugger_text);
        main_window.display();
    }
}
