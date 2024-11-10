#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "constants.hpp"

sf::CircleShape Circle(const float r) {
  const float radius = r * 50;
  sf::CircleShape circle;

  circle.setRadius(radius);
  circle.setOrigin(radius, radius);
  circle.setPosition(centreX, centreY);

  circle.setFillColor(sf::Color::Transparent);

  circle.setOutlineThickness(4.f);
  circle.setOutlineColor(graphColor);

  return circle;
}
