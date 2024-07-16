#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::CircleShape Ellipse() {
    float radius = 6.f;
    const float r = 10*radius; // upscaled for our graph
    const float a = 3;
    const float b = 1;

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
