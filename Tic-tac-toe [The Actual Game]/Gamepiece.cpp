#include "Gamepiece.h"

Gamepiece::Gamepiece(float size_x, float size_y, sf::Vector2f init_pos)
{
    this->piece = sf::RectangleShape(sf::Vector2f(size_x,size_y));
    this->piece.setOutlineColor(sf::Color::Black);
    this->piece.setOutlineThickness(-3.f);
    this->piece.setPosition(init_pos);
}

Gamepiece::Gamepiece(float size_x, float size_y, sf::Vector2f init_pos, char t_piecetype, sf::Font& font)
{
    this->piece = sf::RectangleShape(sf::Vector2f(size_x,size_y));
    this->piece.setOutlineColor(sf::Color::Black);
    this->piece.setOutlineThickness(-3.f);
    this->piece.setPosition(init_pos);
    this->t_piecetype.setFont(font);
    this->t_piecetype.setString(t_piecetype);
    this->t_piecetype.setFillColor(sf::Color::Black);
    this->t_piecetype.setCharacterSize(80);
    if (t_piecetype == 'X') this->t_piecetype.setPosition(init_pos.x+25,init_pos.y);
    if (t_piecetype == 'O') this->t_piecetype.setPosition(init_pos.x+22,init_pos.y);
    this->isGamepiece = true;
    this->isMovable = true;
}

sf::RectangleShape Gamepiece::getShape()
{
    return this->piece;
}

bool Gamepiece::getOccupation()
{
    return this->isOccupied;
}

bool Gamepiece::getMovable()
{
    return this->isMovable;
}

void Gamepiece::move(sf::Vector2f position)
{
    this->piece.setPosition(position.x-50,position.y-50);
    if (t_piecetype.getString() == "X") this->t_piecetype.setPosition((position.x+25)-50,position.y-50);
    else if (t_piecetype.getString() == "O") this->t_piecetype.setPosition((position.x+22)-50,position.y-50);
}

void Gamepiece::update(sf::Color color)
{
    this->piece.setFillColor(color);
}

void Gamepiece::updateOccupation(bool occupationState)
{
    this->isOccupied = occupationState;
}

void Gamepiece::updateMovable(bool canMove)
{
    this->isMovable = canMove;
}

void Gamepiece::render(sf::RenderTarget *target)
{
    target->draw(this->piece);
    if (this->isGamepiece) target->draw(this->t_piecetype);
}
