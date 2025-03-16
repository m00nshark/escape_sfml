#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

#include <cmath>
#include "math.h"

#include "ui.h"




int main()
{
    // these lines are for hiding a debug console if in debug mode
    #ifdef NDEBUG
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
    #endif

    // create a main_window, next line - cap it's framerate (and with it - update rate) to 60
    sf::RenderWindow main_window
                     (sf::VideoMode({ 1800, 920 }),
                         "escape the void, the game",
                         sf::Style::Default,
                         sf::State::Windowed);
    main_window.setFramerateLimit(60);
    main_window.clear(sf::Color::Black);
    
    sf::Image main_window_icon("textures/quill.png");
    main_window.setIcon(main_window_icon);

        // init code
    bot_init();
    ui::proc.text_init(main_window.getSize(), true);
    level::tutorial.init();
    
    // create a default and camera view
    sf::View default_view;
    sf::View camera_view;
    // set size&center for views
  
    {
        float x = (main_window.getSize().x / 2);
        float y = (main_window.getSize().y / 2);
        default_view.setCenter( { x, y } );
        camera_view.setCenter({ x, y });
        
        x = main_window.getSize().x;
        y = main_window.getSize().y;
        default_view.setSize({ x, y });
        camera_view.setSize({ x, y });
    }
    bot.setPosition(level::tutorial.spawnpoint);
    // create boolean to toggle between views
    bool view_mode = true; // false for camera_view, true for default_view
    bool view_toggle_helper = false;




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
        // TODO update window and views as it's resized



            //out-of-drawing loop code
        // imo i don't need to explain what's happening here
        key_upd_full();
        bot_loop();
        level::tutorial.collider();
        // updating camera_view as bot moves
        camera_view.setCenter({ bot.getPosition() });
        if (view_mode) camera_view.setRotation(bot.getRotation());
        else camera_view.setRotation(sf::radians(0));
        // updating 
        window_size = main_window.getSize();
        ui::debugger_text.setString(debugtext);
        // handling the view mode
        if (getkey.f2 && !view_toggle_helper) view_toggle_helper = true;
        if (!getkey.f2 && view_toggle_helper)
        {
            view_mode = !view_mode;
            view_toggle_helper = false;
        }
        // fuck last seven lines made me feel stupid, very stupid
        

        main_window.clear(sf::Color::Black);



            // drawing loop code
                // setting view to draw the game thingies
        main_window.setView(camera_view);
        level::tutorial.drawmap(main_window);
        // draw actual game contents
        main_window.draw(bot);



        // setting view to default_view for drawing UI
        main_window.setView(default_view);

        ui::proc.text_loop();
        ////managing tooltip auto-hiding
        //if (!(tooltip_hide_timer.getElapsedTime() > tooltip_autohide_delay))
        //    main_window.draw(tooltip_text);
        ////debug text drawing
        main_window.draw(ui::debugger_text);
        if (ui::draw_tooltip) main_window.draw(ui::tooltip_text);
        
        main_window.display();
    }
}
