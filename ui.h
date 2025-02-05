#pragma once

namespace ui
{
    //init terminus font
    sf::Font f_terminus("fonts/terminus.ttf");
    // init text, currently for debug goals
    sf::Text debugger_text(f_terminus);
    // init text for key binding tooltip
    sf::Text tooltip_text(f_terminus);
    // 07:05 P.M., 3feb2025: my brain catched a null pointer exception. further descriptions are not going to be made
    sf::Clock tooltip_hide_timer;
    sf::Time tooltip_autohide_delay = sf::seconds(6);
    sf::Vector2u window_size;
    bool draw_tooltip = true;
    sf::RenderWindow window;

	class
	{
		bool is_debug_enabled = false;



	public:

		// initialize the UI, pass the window size and boolean for toggling debugger text (last - TODO)
		void text_init(sf::Vector2u w_s, bool debug)
		{
            window_size = w_s;

            debugger_text.setCharacterSize(36);
            debugger_text.setFillColor(sf::Color::White);
            debugger_text.setStyle(sf::Text::Regular);
            debugger_text.setString("not updated, check code");
            debugger_text.setPosition({ 10.f, (window_size.y - 50.f) });
            
            tooltip_text.setCharacterSize(24);
            tooltip_text.setFillColor(sf::Color::White);
            tooltip_text.setStyle(sf::Text::Regular);
            tooltip_text.setPosition({ 10.f, 10.f });
            tooltip_text.setString
            (" W/S - acceleration \n A/D - rotation \n A+D - u-turn \n Q/E - side move \n Q+E - stop \n F2 - toggle view mode \n F1 - show this tooltip");
            tooltip_text.setOutlineThickness(1);

            // init timer for autohiding tooltip
            tooltip_hide_timer.restart();

		}

		void text_loop()
		{
            // handling auto-hiding of tooltip
            if (getkey.f1) tooltip_hide_timer.restart();
            if (!(tooltip_hide_timer.getElapsedTime() > tooltip_autohide_delay))
                draw_tooltip = true;
            else draw_tooltip = false;

            // updating debug stats
            debugger_text.setString(debugtext);
		}
	}proc;
}