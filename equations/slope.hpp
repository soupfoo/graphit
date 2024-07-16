#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::VertexArray Slope() {
    const float m = 0.5f;
    const float c = 15.f;

    sf::VertexArray sl(sf::TrianglesStrip);

    for (float x = left; x <= right; x += 1) {
        float y = centreY - (m * (x - centreX) + 5*c);
        if ( y<=top || y>=bottom)
            continue;
        sl.append(sf::Vertex(sf::Vector2f(x, y-2), graphColor));
        sl.append(sf::Vertex(sf::Vector2f(x, y+2), graphColor));
    }
    return sl;
}
