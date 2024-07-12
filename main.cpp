#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <cmath>
#include "equations/parabola.hpp"
#include "equations/sine.hpp"
#include "equations/cosine.hpp"
#include "equations/circle.hpp"
#include "equations/slope.hpp"


sf::VertexArray createAxes() {
    sf::VertexArray axes(sf::Lines);
    // (X-axis)
    axes.append(sf::Vertex(sf::Vector2f(left, centreY), axisColor));
    axes.append(sf::Vertex(sf::Vector2f(right, centreY), axisColor));
    // (Y-axis)
    axes.append(sf::Vertex(sf::Vector2f(centreX, top), axisColor));
    axes.append(sf::Vertex(sf::Vector2f(centreX, bottom), axisColor));

    return axes;
}

void clearGraph(bool g[]) {
    for (int i = 0; i < 8; i++) {
        g[i] = false;
    }
}

bool MouseHover(const sf::RectangleShape& btn, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f btnPos = btn.getPosition();
    sf::Vector2f btnSize = btn.getSize();

    if (mousePos.x >= btnPos.x && mousePos.x <= btnPos.x + btnSize.x &&
        mousePos.y >= btnPos.y && mousePos.y <= btnPos.y + btnSize.y) {
        return true;
    }
    return false;
}

bool MouseClicked(const sf::RectangleShape& btn, sf::RenderWindow& window) {
    return sf::Mouse::isButtonPressed(sf::Mouse::Left) && MouseHover(btn, window);
}

int main() {
    sf::Color bg(28, 28, 25);
    sf::Color btnColor(52, 53, 43);
    sf::Color text(234, 234, 227);
    sf::Color outlineActive(130, 130, 119);
    const int windowWidth = 1600, windowHeight = 900;
    
    bool drawGraph[8];
    clearGraph(drawGraph);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Graphit");

    int btnWidth = window.getSize().x / 4 - 50;
    int btnHeight = (window.getSize().y) / 16;
    int fontSize = std::min(btnWidth / 10, btnHeight / 3);

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;

    int numButtons = 8;

    sf::Font font;
    font.loadFromFile("jetbrainsmono.ttf");

    std::vector<std::string> buttontext{
        "sine wave",
        "cosine wave",
        "parabola",
        "slope",
        "hyperbola",
        "circle",
        "ellipse",
        "vector"
    };

    sf::VertexArray sineWave, slope, cosWave, parabola;
    sf::CircleShape circle;
    sineWave = Sine();
    slope = Slope();
    circle = Circle();
    cosWave = Cosine();
    parabola = Parabola();

    sf::VertexArray axes = createAxes();

    for (int i = 0; i < numButtons; ++i) {
        sf::RectangleShape btn(sf::Vector2f(btnWidth, btnHeight));
        btn.setPosition(10, 10 + i * (btnHeight + 10));
        sf::Text btnText(buttontext[i], font, fontSize);
        btnText.setPosition(
            btn.getPosition().x + (btn.getSize().x / 2) - (btnText.getGlobalBounds().width / 2),
            btn.getPosition().y + (btn.getSize().y / 2) - (btnText.getGlobalBounds().height / 2)
        );

        buttons.push_back(btn);
        buttonTexts.push_back(btnText);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < numButtons; ++i) {
            if (MouseClicked(buttons[i], window)) {
                for (int j = 0; j < int(buttons.size()); ++j) {  
                    buttons[j].setOutlineThickness(0);
                }

                buttons[i].setFillColor(btnColor);
                buttons[i].setOutlineColor(outlineActive);
                buttons[i].setOutlineThickness(4);

                clearGraph(drawGraph);
                drawGraph[i] = true;

            } else {
                buttons[i].setFillColor(btnColor);
                buttonTexts[i].setFillColor(text);
            }
        }

        window.clear(bg);
        window.draw(axes);

        for (int i = 0; i < numButtons; ++i) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
        if (drawGraph[0]) {
            window.draw(sineWave);
        }
        if (drawGraph[3]) {
            window.draw(slope);
        }
        if (drawGraph[5]) {
            window.draw(circle);
        }
        if (drawGraph[1]) {
            window.draw(cosWave);
        }
        if (drawGraph[2]) {
            window.draw(parabola);
        }

        window.display();
    }

    return 0;
}
