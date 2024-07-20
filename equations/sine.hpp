#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "vars.hpp"

sf::VertexArray Sine(const float a, const float f) {
    const float amplitude = a*50;
    const float frequency = f/50;
    const float phaseShift = 0.f;

    sf::VertexArray sineWave(sf::TrianglesStrip);

    for (float x = left; x <= right; x += 1) {
        float y = amplitude * std::sin(frequency * (x - centreX) + phaseShift) + centreY;
        sineWave.append(sf::Vertex(sf::Vector2f(x, y-2), graphColor ));
        sineWave.append(sf::Vertex(sf::Vector2f(x, y+2), graphColor ));
    }

    return sineWave;
}
