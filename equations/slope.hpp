#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <cmath>
#include "vars.hpp"

sf::VertexArray Slope() {
    const float m = 1.f;
    const float c = 0.f;

    sf::VertexArray slope(sf::TrianglesStrip);

    for (float x = left; x <= right; x += 1) {
        float y = centreY - (m * (x - centreX) + 5*c);
        if ( y<=top || y>=bottom)
            continue;
        slope.append(sf::Vertex(sf::Vector2f(x, y-2), graphColor));
        slope.append(sf::Vertex(sf::Vector2f(x, y+2), graphColor));
    }
    return slope;
}