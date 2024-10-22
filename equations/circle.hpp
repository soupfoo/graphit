#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::CircleShape Circle(const float r) {
    const float radius = r*50;

    sf::CircleShape cr;
    cr.setRadius(radius);
    cr.setOutlineThickness(4.f);
    cr.setOutlineColor(graphColor);
    cr.setFillColor(sf::Color::Transparent);
    cr.setOrigin(radius, radius);
    cr.setPosition(centreX, centreY);

    return cr;
}
