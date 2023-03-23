#include "./Headers/Player.h"

using namespace sf;

#define GAME_NAME "Mario Lite"

int main()
{
    Player mario;
    RenderWindow window(sf::VideoMode(700, 400), GAME_NAME);

    sf::Clock clock;
    while (window.isOpen())
    {
        double time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/500;
        if (time > 20)
            time = 20;
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
            mario.xDirection = -1; 
       
	    if (Keyboard::isKeyPressed(Keyboard::Right))
            mario.xDirection = 1;
    
        mario.update(time);

        window.clear(sf::Color::White);
        window.draw(mario.sprite);
        window.display();
    }

    return 0;
}