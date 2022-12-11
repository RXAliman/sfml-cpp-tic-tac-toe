#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>

class Gamepiece {
private:
    sf::RectangleShape piece;
    sf::Vector2f pos;
    sf::Text t_piecetype;
    bool isOccupied;
    bool isGamepiece;
    bool isMovable;
public:
    Gamepiece(float size_x, float size_y, sf::Vector2f init_pos);
    Gamepiece(float size_x, float size_y, sf::Vector2f init_pos, char t_piecetype, sf::Font &font);
    sf::RectangleShape getShape();
    bool getOccupation();
    bool getMovable();
    void move(sf::Vector2f position);
    void update(sf::Color color);
    void updateOccupation(bool occupationState);
    void updateMovable(bool canMove = false);
    void render(sf::RenderTarget *target);
};
