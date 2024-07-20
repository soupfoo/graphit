#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::VertexArray Parabola(const float a) {
    sf::VertexArray pb(sf::TrianglesStrip);

    for (float x = right; x >= centreX; x--) {
        float y1 = sqrt(4*a*(x-centreX)) + centreY;
        pb.append(sf::Vertex(sf::Vector2f(x, y1-2), graphColor));
        pb.append(sf::Vertex(sf::Vector2f(x, y1+2), graphColor));
    }
    for (float x = centreX; x <= right; x++) {
        float y2 = -sqrt(4*a*(x-centreX)) + centreY;
        pb.append(sf::Vertex(sf::Vector2f(x, y2-2), graphColor));
        pb.append(sf::Vertex(sf::Vector2f(x, y2+2), graphColor));
    }
    return pb;
}
