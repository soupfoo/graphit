#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::VertexArray vertex_calc(const float _a, const float _b, const int sign) {
    const float a = 50*_a;
    const float b = 50*_b;
    const float minX = -a*2;
    const float maxX = a*2;
    sf::VertexArray hyperbola(sf::TrianglesStrip);

    for (float x = minX; x <= maxX; x++) {
        float rootTerm = (x * x) / (a * a) + 1;

        if (rootTerm >= 0) {
            float y1 = b * sqrt(rootTerm);
            hyperbola.append(sf::Vertex(sf::Vector2f(sign*y1+centreX+2, x+centreY), graphColor));
            hyperbola.append(sf::Vertex(sf::Vector2f(sign*y1+centreX-2, x+centreY), graphColor));
        }
    }
    return hyperbola;
}

sf::VertexArray Hyper_left(const float _a, const float _b) {
    return vertex_calc(_a, _b, -1);
}

sf::VertexArray Hyper_right(const float _a, const float _b) {
    return vertex_calc(_a, _b, 1);
}
