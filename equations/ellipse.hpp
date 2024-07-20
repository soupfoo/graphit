#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::CircleShape Ellipse(const float a, const float b) {
    const float r = 50;

    sf::CircleShape elsp;
    elsp.setRadius(r);
    elsp.setOutlineThickness(2.f);
    elsp.setOutlineColor(graphColor);
    elsp.setFillColor(sf::Color::Transparent);
    elsp.setScale(a,b);
    elsp.setOrigin(r, r);
    elsp.setPosition(centreX, centreY);

    return elsp;
}
