#include "Application.h"

int main()
{
    Application app;
    while (app.getWindow()->isOpen())
    {
        app.update();
        app.render();
    }
    return 0;
}

/*
#include <SFML/Graphics.hpp>
#include <sstream>

int main()
{
    sf::RenderWindow* window;
    sf::Event event;
    sf::Clock timer;
    sf::Font tahoma;
    sf::Text t_timer;

    const int max_sec = 2;

    window = new sf::RenderWindow(sf::VideoMode(800,600),"Test",sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(60);

    tahoma.loadFromFile("resources/tahoma.ttf");
    t_timer.setFont(tahoma);

    while (window->isOpen())
    {
        static bool done;
        if (!done)
        {
            std::stringstream ss;
            int l = max_sec * 100 - timer.getElapsedTime().asMilliseconds()/10;
            int n = l / 100;
            int m = l - n * 100;
            if (n <= 0 && m <= 0)
            {
                n = 0; m = 0;
                done = true;
            }
            if (n < 10) ss << 0;
            ss << n << ":";
            if (m < 10) ss << 0;
            ss << m;
            t_timer.setString(ss.str());
        }
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window->close();
            }
        }

        window->clear();
        window->draw(t_timer);
        window->display();
    }

    delete window;
}
*/
