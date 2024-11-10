#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>

#include "constants.hpp"

sf::VertexArray Cosine(const float a, const float f) {
  const float amplitude = a * 50;
  const float frequency = f / 50;
  const float phaseShift = 0.f;
  const float verticalOffset = 450.f;

  sf::VertexArray cosineWave(sf::TrianglesStrip);

  for (float x = left; x <= right; x += 1) {
    float y = -amplitude * std::cos(frequency * (x - centreX) + phaseShift) +
              verticalOffset;
    cosineWave.append(sf::Vertex(sf::Vector2f(x, y - 2), graphColor));
    cosineWave.append(sf::Vertex(sf::Vector2f(x, y + 2), graphColor));
  }
  return cosineWave;
}
