#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::VertexArray Cosine() {
    const float amplitude = 150.f;
    const float frequency = 0.015f;
    const float phaseShift = 0.f;
    const float verticalOffset = 450.f;

    sf::VertexArray cosineWave(sf::TrianglesStrip);

    for (float x = left; x <= right; x += 1) {
        float y = -amplitude * std::cos(frequency * (x - centreX) + phaseShift) + verticalOffset;
        cosineWave.append(sf::Vertex(sf::Vector2f(x, y-2), graphColor));
        cosineWave.append(sf::Vertex(sf::Vector2f(x, y+2), graphColor));
    }
    return cosineWave;
}
