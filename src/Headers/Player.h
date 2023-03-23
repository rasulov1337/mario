#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
    public:
        explicit Player();
        
        void update(double dt);

        sf::Sprite sprite;
        sf::FloatRect rect;

        int xDirection;
        int yDirection;

    private:
        sf::Texture texture;
        double currentFrame;

        int _speed;

        void processAnimation();

};