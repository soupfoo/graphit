#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <cmath>
#include "vars.hpp"

sf::CircleShape Circle() {
    const float radius = 200.0f;
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setOutlineThickness(4.f);
    circle.setOutlineColor(graphColor);
    circle.setFillColor(sf::Color::Transparent); 
    circle.setPosition(centreX-radius, centreY-radius);

    return circle;
}