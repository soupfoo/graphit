#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>

#include "constants.hpp"

sf::VertexArray CalculateVertex(const float &_a, const float &_b,
                                const int &sign) {
  const float a = _a * 50;
  const float b = _b * 50;
  const float minX = -a * 2;
  const float maxX = a * 2;

  sf::VertexArray hyperbola(sf::TrianglesStrip);

  for (float x = minX; x <= maxX; x++) {
    float rootTerm = (x * x) / (a * a) + 1;

    if (rootTerm >= 0) {
      float y = b * std::sqrt(rootTerm);

      hyperbola.append(sf::Vertex(
          sf::Vector2f(sign * y + centreX + 2, x + centreY), graphColor));

      hyperbola.append(sf::Vertex(
          sf::Vector2f(sign * y + centreX - 2, x + centreY), graphColor));
    }
  }

  return hyperbola;
}

sf::VertexArray LeftHyperBola(const float &a, const float &b) {
  return CalculateVertex(a, b, -1);
}

sf::VertexArray RightHyperBola(const float &a, const float &b) {
  return CalculateVertex(a, b, 1);
}
