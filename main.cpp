#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <cmath>
#include "equations/vars.hpp"
#include "equations/parabola.hpp"
#include "equations/sine.hpp"
#include "equations/hyperbola.hpp"
#include "equations/cosine.hpp"
#include "equations/circle.hpp"
#include "equations/slope.hpp"
#include "equations/ellipse.hpp"

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
    bool drawGraph[8];
    clearGraph(drawGraph);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "GraphIt");

    int btnWidth = window.getSize().x / 4 - 50;
    int btnHeight = (window.getSize().y) / 16;
    int fontSize = std::min(btnWidth / 10, btnHeight / 3);

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;

    int numButtons = 7;

    sf::Font font;
    font.loadFromFile("jetbrainsmono.ttf");

    std::vector<std::string> buttontext{
        "sine wave",
        "cosine wave",
        "parabola",
        "slope",
        "hyperbola",
        "circle",
        "ellipse"
    };

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

       sf::RectangleShape graphBg(sf::Vector2f(right-left, bottom-top));
       graphBg.setPosition(left, top );
       graphBg.setFillColor(sf::Color(graphBgColor));

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
        window.draw(graphBg);
        window.draw(axes);

        for (int i = 0; i < numButtons; ++i) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
        if (drawGraph[0]) {
            window.draw(Sine());
        }
        if (drawGraph[1]) {
            window.draw(Cosine());
        }
        if (drawGraph[2]) {
            window.draw(Parabola());
        }
        if (drawGraph[3]) {
            window.draw(Slope());
        }
        if (drawGraph[4]) {
            window.draw(Hyper_left());
            window.draw(Hyper_right());
        }
        if (drawGraph[5]) {
            window.draw(Circle());
        }
        if (drawGraph[6]) {
            window.draw(Ellipse());
        }

        window.display();
    }

    return 0;
}
