#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>

#include "constants.hpp"

sf::VertexArray StraightLine(const float &m, const float &c) {
  sf::VertexArray line(sf::TrianglesStrip);

  for (float x = left; x <= right; x += 1) {
    float y = centreY - (m * (x - centreX) + c * 50);
    if (y <= top || y >= bottom) continue;

    line.append(sf::Vertex(sf::Vector2<float>(x, y - 2), graphColor));
    line.append(sf::Vertex(sf::Vector2<float>(x, y + 2), graphColor));
  }

  return line;
}
