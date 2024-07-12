#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <cmath>
#include "vars.hpp"

sf::VertexArray Parabola() {
    const float a = 15;
    sf::VertexArray parabola(sf::TrianglesStrip);

    for (float x = right; x >= centreX; x--) {
        float y1 = sqrt(4*a*(x-centreX)) + centreY;
        parabola.append(sf::Vertex(sf::Vector2f(x, y1-2), graphColor));
        parabola.append(sf::Vertex(sf::Vector2f(x, y1+2), graphColor));
    }
    for (float x = centreX; x <= right; x++) {
        float y2 = -sqrt(4*a*(x-centreX)) + centreY;
        parabola.append(sf::Vertex(sf::Vector2f(x, y2-2), graphColor));
        parabola.append(sf::Vertex(sf::Vector2f(x, y2+2), graphColor));
}
    return parabola;
}