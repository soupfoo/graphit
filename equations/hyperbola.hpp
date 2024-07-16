#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::VertexArray vertex_calc(int sign) {
    sf::VertexArray hyperbola(sf::TrianglesStrip);
    const float step = 1.f;
    const float _a = 6.f;
    const float _b = 6.f;

    // scaling up a,b for our graph
    const float a = 20*_a;
    const float b = 20*_b;

    const float minX = -a*2;
    const float maxX = a*2;

    for (float x = minX; x <= maxX; x += step) {
        float rootTerm = (x * x) / (a * a) + 1;

        if (rootTerm >= 0) {
            float y1 = b * sqrt(rootTerm);
            hyperbola.append(sf::Vertex(sf::Vector2f(sign*y1+centreX+2, x+centreY), graphColor));
            hyperbola.append(sf::Vertex(sf::Vector2f(sign*y1+centreX-2, x+centreY), graphColor));
        }
    }
    return hyperbola;
}

sf::VertexArray Hyper_left() {
    return vertex_calc(-1);
}

sf::VertexArray Hyper_right() {
    return vertex_calc(1);
}
