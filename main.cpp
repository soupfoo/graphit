#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <sstream>
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

sf::VertexArray createGrid() {
    sf::VertexArray grid(sf::Lines);

    for (int i=top; i <= bottom; i+=50) {
        grid.append(sf::Vertex(sf::Vector2f(left, i), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(right, i), gridColor));
    }

    for (int j=left; j <= right; j+=50) {
        grid.append(sf::Vertex(sf::Vector2f(j, top), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(j, bottom), gridColor));
    }
    return grid;
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

void handleInput(sf::Event event, bool &inputComplete, std::string &input, sf::Text &displayText, const std::string &prompt) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\r') {
            inputComplete = true;
        }
        else if (event.text.unicode == 8) {
            if (!input.empty()) {
                input.pop_back();
                displayText.setString(prompt + input);
            }
        }
        else if (event.text.unicode < 128) {
            input += static_cast<char>(event.text.unicode);
            displayText.setString(prompt + input);
        }
    }
}

int main() {
    bool drawGraph[8];
    clearGraph(drawGraph);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "GraphIt", sf::Style::Titlebar | sf::Style::Close);

    const int btnWidth = window.getSize().x / 4 - 50;
    const int btnHeight = (window.getSize().y) / 16;
    const int fontSize = std::min(btnWidth / 10, btnHeight / 3);

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
    sf::VertexArray grids = createGrid();

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

    sf::Text outputtext;
    outputtext.setFont(font);
    outputtext.setCharacterSize(fontSize);
    outputtext.setFillColor(text);
    outputtext.setPosition(25, 505);

    sf::RectangleShape inputBox(sf::Vector2f(btnWidth, btnHeight*4));
    inputBox.setPosition(10, 500);
    inputBox.setFillColor(graphBgColor);
    inputBox.setOutlineColor(outlineActive);
    inputBox.setOutlineThickness(2);
    std::string input;
    bool inputComplete = false;
    std::string currentPrompt;

    std::vector<std::string> prompts{
        "Input amplitude\nand frequency:\n\n",
        "Input amplitude\n and frequency:\n\n",
        "Input a:\n\n",
        "Input m and c:\n\n",
        "Input a and b:\n\n",
        "Input radius:\n\n",
        "Input a and b:\n\n"};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            handleInput(event, inputComplete, input, outputtext, currentPrompt);
        }

        for (int i = 0; i < numButtons; ++i) {
            if (MouseClicked(buttons[i], window)) {
                inputBox.setOutlineThickness(2);
                inputBox.setOutlineColor(gridColor);
                for (int j = 0; j < int(buttons.size()); ++j) {
                    buttons[j].setOutlineThickness(0);
                }

                buttons[i].setFillColor(btnColor);
                buttons[i].setOutlineColor(outlineActive);
                buttons[i].setOutlineThickness(4);

                clearGraph(drawGraph);
                drawGraph[i] = true;

                input.clear();
                currentPrompt = prompts[i];
                outputtext.setString(currentPrompt);
            } else {
                buttons[i].setFillColor(btnColor);
                buttonTexts[i].setFillColor(text);
            }
        }

        window.clear(bg);
        window.draw(graphBg);
        window.draw(grids);
        window.draw(axes);
        window.draw(inputBox);
        window.draw(outputtext);

        for (int i = 0; i < numButtons; ++i) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
        if (MouseClicked(inputBox, window)) {
                inputBox.setOutlineThickness(5);
                inputBox.setOutlineColor(outlineActive);
        }
        if (drawGraph[0]) {
            std::stringstream ss(input);
            float a, f;
            ss >> a >> f;
            window.draw(Sine(a, f));
        }
        if (drawGraph[1]) {
            std::stringstream ss(input);
            float a, f;
            ss >> a >> f;
            window.draw(Cosine(a, f));
        }
        if (drawGraph[2]) {
            std::stringstream ss(input);
            float a;
            ss >> a;
            window.draw(Parabola(a));
        }
        if (drawGraph[3]) {
            std::stringstream ss(input);
            float m, c;
            ss >> m >> c;
            window.draw(Slope(m, c));
        }
        if (drawGraph[4]) {
            std::stringstream ss(input);
            float a, b;
            ss >> a >> b;
            window.draw(Hyper_left(a, b));
            window.draw(Hyper_right(a, b));
        }
        if (drawGraph[5]) {
            std::stringstream ss(input);
            float r;
            ss >> r;
            window.draw(Circle(r));
        }
        if (drawGraph[6]) {
            std::stringstream ss(input);
            float a, b;
            ss >> a >> b;
            window.draw(Ellipse(a, b));
        }

        window.display();
    }

    return 0;
}
