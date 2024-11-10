#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib>
#include <sstream>
#include <string>

#include "constants.hpp"
#include "equations/circle.hpp"
#include "equations/cosine.hpp"
#include "equations/ellipse.hpp"
#include "equations/hyperbola.hpp"
#include "equations/parabola.hpp"
#include "equations/sine.hpp"
#include "equations/slope.hpp"

sf::VertexArray createAxes();
sf::VertexArray createGrids();

bool IsHovering(const sf::RectangleShape& button, sf::RenderWindow& window);
bool IsMouseClicked(const sf::RectangleShape& button, sf::RenderWindow& window);

void HandleInput(sf::Event event, bool& inputComplete, std::wstring& input,
                 sf::Text& displayText, const std::wstring& prompt);

const std::string appName = "GraphIt";

/**
 * TODO: Instead of hard code, turn graphs to classes and set which graphs to
 * show or clear.
 */
void clearGraph(bool g[]) {
  for (int i = 0; i < 7; i++) {
    g[i] = false;
  }
}

int main() {
  bool drawGraph[7];
  clearGraph(drawGraph);

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), appName,
                          sf::Style::Titlebar | sf::Style::Close);

  const int buttonWidth = window.getSize().x / 4 - 50;
  const int buttonHeight = (window.getSize().y) / 16;

  const int fontSize = std::min(buttonWidth / 10, buttonHeight / 3);

  sf::Font font;

  // TODO: Load with absolute path
  font.loadFromFile("./assets/jetbrainsmono.ttf");

  std::vector<sf::RectangleShape> buttons;
  std::vector<sf::Text> buttonTexts;

  std::vector<std::string> equations{"Sine wave", "Cosine wave", "Parabola",
                                     "Slope",     "Hyperbola",   "Circle",
                                     "Ellipse"};

  sf::VertexArray axes = createAxes();
  sf::VertexArray grids = createGrids();

  for (int i = 0; i < equations.size(); ++i) {
    sf::RectangleShape button(sf::Vector2<float>(buttonWidth, buttonHeight));
    button.setPosition(10, 10 + i * (buttonHeight + 10));

    sf::Text buttonText(equations[i], font, fontSize);
    const int buttonTextX = button.getPosition().x + (button.getSize().x / 2) -
                            (buttonText.getGlobalBounds().width / 2);

    const int buttonTextY = button.getPosition().y + (button.getSize().y / 2) -
                            (buttonText.getGlobalBounds().height / 2);
    buttonText.setPosition(buttonTextX, buttonTextY);

    buttons.push_back(button);
    buttonTexts.push_back(buttonText);
  }

  sf::RectangleShape graphBg(sf::Vector2<float>(right - left, bottom - top));
  graphBg.setPosition(left, top);
  graphBg.setFillColor(sf::Color(graphBgColor));

  sf::Text outputText;
  outputText.setFont(font);
  outputText.setCharacterSize(fontSize);
  outputText.setFillColor(textColor);
  outputText.setPosition(25, 505);

  sf::RectangleShape inputBox(
      sf::Vector2<float>(buttonWidth, buttonHeight * 4));

  inputBox.setPosition(10, 500);
  inputBox.setFillColor(graphBgColor);
  inputBox.setOutlineColor(outlineActive);
  inputBox.setOutlineThickness(2);

  // TODO: Make strings work cross-platform.
  std::wstring input;
  std::wstring currentPrompt;
  bool inputComplete = false;

  std::vector<std::wstring> prompts{
      L"y(t) = Asin(2πft+ϕ)\n\nInput amplitude\nand frequency:\n\n",
      L"y(t) = Acos(2πft+ϕ)\n\nInput amplitude\nand frequency:\n\n",
      L"y = 4ax\n\nInput a:\n\n",
      L"y = mx+c\n\nInput m and c:\n\n",
      L"x^2/a^2 - y^2/b^2 = 1\n\nInput a and b:\n\n",
      L"x^2 + y^2 = r^2\n\nInput radius:\n\n",
      L"x^2/a^2 + y^2/b^2 = 1\n\nInput a and b:\n\n"};

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      HandleInput(event, inputComplete, input, outputText, currentPrompt);
    }

    for (int i = 0; i < equations.size(); ++i) {
      if (IsMouseClicked(buttons[i], window)) {
        inputBox.setOutlineThickness(2);
        inputBox.setOutlineColor(gridColor);
        for (int j = 0; j < int(buttons.size()); ++j) {
          buttons[j].setOutlineThickness(0);
        }

        buttons[i].setFillColor(buttonColor);
        buttons[i].setOutlineColor(outlineActive);
        buttons[i].setOutlineThickness(4);

        clearGraph(drawGraph);
        drawGraph[i] = true;

        input.clear();
        currentPrompt = prompts[i];
        outputText.setString(currentPrompt);

      } else {
        buttons[i].setFillColor(buttonColor);
        buttonTexts[i].setFillColor(textColor);
      }
    }

    window.clear(bgColor);
    window.draw(graphBg);
    window.draw(grids);
    window.draw(axes);
    window.draw(inputBox);
    window.draw(outputText);

    for (int i = 0; i < equations.size(); ++i) {
      window.draw(buttons[i]);
      window.draw(buttonTexts[i]);
    }

    if (IsMouseClicked(inputBox, window)) {
      inputBox.setOutlineThickness(5);
      inputBox.setOutlineColor(outlineActive);
    }

    // TODO: Find a better way to do this.
    if (drawGraph[0]) {
      std::wstringstream ss(input);
      float a, f;
      ss >> a >> f;
      window.draw(Sine(a, f));
    }
    if (drawGraph[1]) {
      std::wstringstream ss(input);
      float a, f;
      ss >> a >> f;
      window.draw(Cosine(a, f));
    }
    if (drawGraph[2]) {
      std::wstringstream ss(input);
      float a;
      ss >> a;
      window.draw(Parabola(a));
    }
    if (drawGraph[3]) {
      std::wstringstream ss(input);
      float m, c;
      ss >> m >> c;
      window.draw(StraightLine(m, c));
    }
    if (drawGraph[4]) {
      std::wstringstream ss(input);
      float a, b;
      ss >> a >> b;
      window.draw(LeftHyperBola(a, b));
      window.draw(RightHyperBola(a, b));
    }
    if (drawGraph[5]) {
      std::wstringstream ss(input);
      float r;
      ss >> r;
      window.draw(Circle(r));
    }
    if (drawGraph[6]) {
      std::wstringstream ss(input);
      float a, b;
      ss >> a >> b;
      window.draw(Ellipse(a, b));
    }

    window.display();
  }

  return EXIT_SUCCESS;
}

sf::VertexArray createAxes() {
  sf::VertexArray axes(sf::Lines);

  // (X-axis)
  axes.append(sf::Vertex(sf::Vector2<float>(left, centreY), axisColor));
  axes.append(sf::Vertex(sf::Vector2<float>(right, centreY), axisColor));

  // (Y-axis)
  axes.append(sf::Vertex(sf::Vector2<float>(centreX, top), axisColor));
  axes.append(sf::Vertex(sf::Vector2<float>(centreX, bottom), axisColor));

  return axes;
}

sf::VertexArray createGrids() {
  sf::VertexArray grids(sf::Lines);
  const int gridGap = 50;

  // Vertical grids:
  for (int i = top; i <= bottom; i += gridGap) {
    grids.append(sf::Vertex(sf::Vector2<float>(left, i), gridColor));
    grids.append(sf::Vertex(sf::Vector2<float>(right, i), gridColor));
  }

  // Horizontal grids:
  for (int i = left; i <= right; i += gridGap) {
    grids.append(sf::Vertex(sf::Vector2<float>(i, top), gridColor));
    grids.append(sf::Vertex(sf::Vector2<float>(i, bottom), gridColor));
  }

  return grids;
}

bool IsHovering(const sf::RectangleShape& button, sf::RenderWindow& window) {
  sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);
  sf::Vector2<float> buttonPos = button.getPosition();
  sf::Vector2<float> buttonSize = button.getSize();

  return (
      mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x &&
      mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y);
}

bool IsMouseClicked(const sf::RectangleShape& button,
                    sf::RenderWindow& window) {
  return sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
         IsHovering(button, window);
}

void HandleInput(sf::Event event, bool& inputComplete, std::wstring& input,
                 sf::Text& displayText, const std::wstring& prompt) {
  if (event.type == sf::Event::TextEntered) {
    if (event.text.unicode == '\r') {
      inputComplete = true;

    } else if (event.text.unicode == 8) {
      if (!input.empty()) {
        input.pop_back();
        displayText.setString(prompt + input);
      }

    } else {
      input += static_cast<char>(event.text.unicode);
      displayText.setString(prompt + input);
    }
  }
}
