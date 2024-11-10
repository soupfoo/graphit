#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>

#include "constants.hpp"

sf::VertexArray Parabola(const float &a) {
  sf::VertexArray parabola(sf::TrianglesStrip);

  for (float x = right; x >= centreX; x--) {
    float y = std::sqrt(4 * a * (x - centreX)) + centreY;

    parabola.append(sf::Vertex(sf::Vector2f(x, y - 2), graphColor));
    parabola.append(sf::Vertex(sf::Vector2f(x, y + 2), graphColor));
  }

  for (float x = centreX; x <= right; x++) {
    float y = -std::sqrt(4 * a * (x - centreX)) + centreY;

    parabola.append(sf::Vertex(sf::Vector2f(x, y - 2), graphColor));
    parabola.append(sf::Vertex(sf::Vector2f(x, y + 2), graphColor));
  }

  return parabola;
}
