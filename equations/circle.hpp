#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::CircleShape Circle() {
    const float radius = 200.f;

    sf::CircleShape cr;
    cr.setRadius(radius);
    cr.setOutlineThickness(4.f);
    cr.setOutlineColor(graphColor);
    cr.setFillColor(sf::Color::Transparent);
    cr.setPosition(centreX-radius, centreY-radius);

    return cr;
}
