#pragma once

#include "constants.hpp"

sf::CircleShape Ellipse(const float a, const float b) {
  const float radius = 50;
  sf::CircleShape ellipse;

  ellipse.setOrigin(radius, radius);
  ellipse.setRadius(radius);
  ellipse.setPosition(centreX, centreY);
  ellipse.setScale(a, b);

  ellipse.setFillColor(sf::Color::Transparent);

  ellipse.setOutlineThickness(2.f);
  ellipse.setOutlineColor(graphColor);

  return ellipse;
}
