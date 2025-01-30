/*
        a main file. all sturr related to window mgmt should be put here and not anywhere else.
        (reminder for myself)
*/

#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <cmath>
#include "server.h"
#include "client.h"
#include "math.h"


/*

class texture
{

}

 */

class bot_mvmnt_propts_ {                                                // bot phys properties
    float dx = 0;
    float dy = 0;
    sf::Angle angl = sf::degrees(0.f);
    sf::Angle rot_angl = sf::degrees(3.f);
    float speed = 0.f;
    bool d_pressed = 0;
    bool a_pressed = 0;
    float speedLimit = 10;
    float accel = .3;
    float rotate_angl = 0.1f;
    sf::Texture* t_bot_aliquam = NULL;
    sf::Sprite* bot_aliquam;

public:

    void bot_init()
    {
        t_bot_aliquam->loadFromFile("Textures/bot_aliquam.png");
        bot_aliquam->setTexture(t_bot_aliquam);
        bot_aliquam->setOrigin({ 12.f, 12.f });
        bot_aliquam->setScale({ 4.f, 4.f });
        bot_aliquam->setPosition({ 640,360 });
    }

    sf::Sprite* getSprite()
    {
        return &bot_aliquam;
    }

    void incSpeed()
    {
        speed += accel;
        speed = fmin(speed, speedLimit);
    }
    void decSpeed()
    {
        speed -= accel;
        speed = fmax(speed, -speedLimit);
    }
    void setAccel(float accel_) { accel = accel_; }

    void rotate_right()
    { 
        angl += sf::degrees(rotate_angl);
    }
    void rotate_left()
    {
        angl -= sf::degrees(rotate_angl);
    }

    void stop()
    {
        if (!(abs(speed) < 0.1))
        {
            if (speed < 0) speed += 0.3;
            else speed -= 0.3;
        }
    }

    void actual_moving()
    {
        float bot_dx = speed;
        float bot_dy = 0.f;
        bot_aliquam.setRotation(angl);
        sf::Vector2f vectormove = sf::Vector2f({ bot_dx, bot_dy });
        bot_aliquam.move(vectormove);
    }

} ;

bot_mvmnt_propts_ bot_mvmnt_propts;

int main()
{
    #ifdef NDEBUG                           // these lines are for hiding a debug console if in debug mode
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
    #endif

                                                            // create a window
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "escape the void, the game", sf::Style::Default, sf::State::Windowed);



    const float const_zero = 0.f;

    sf::Clock in0put_timer;                                  // timer section. currently there is only timer for input
    sf::Time input_tick = sf::milliseconds(10);     // 10 stands for 100 updates per second
    float input_timer_elapsed = 0;
    bool input_timer_after_reset = true;

    //sf::Font terminus("fonts/terminus.ttf");                // text... uhm... thing
    //sf::Text lol_its_text(terminus);
    //lol_its_text.setString("lorem ipsum");
    //lol_its_text.setCharacterSize(36);
    //lol_its_text.setFillColor(sf::Color::Green);
    //lol_its_text.setStyle(sf::Text::Regular);
    //lol_its_text.setPosition({ 0.f, 480.f });






    int bot_health = 100;

    bot_mvmnt_propts.bot_init();

    sf::Music caught("music/caught.ogg");                   // music section
    caught.play();
    caught.setPitch(0.90f);
    caught.setVolume(30.f);
    caught.setLooping(true);

    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())      // makes window alive, does event control
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))  // seek for pressing an ESC button, close window if true
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) bot_mvmnt_propts.rotate_left();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) bot_mvmnt_propts.rotate_right();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) bot_mvmnt_propts.incSpeed();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) bot_mvmnt_propts.decSpeed();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) bot_mvmnt_propts.stop();

        bot_mvmnt_propts.actual_moving();

        window.clear(sf::Color::Black);

        window.draw(bot_mvmnt_propts.getSprite());
            
        //window.draw(lol_its_text);

        window.display();
    }
}
