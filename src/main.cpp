#include "Snake.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <map>
#include <optional>

int main() {
  sf::RenderWindow window(sf::VideoMode({BOARD_WIDTH, BOARD_WIDTH}), "SFML");
  window.setFramerateLimit(60);

  const float cellSize = BOARD_WIDTH * 1.f / GRID_SIZE;

  Snake snake(cellSize);
  const std::map<sf::Keyboard::Scan, sf::Vector2i> directions = {
      {sf::Keyboard::Scan::Right, {1, 0}},
      {sf::Keyboard::Scan::Left, {-1, 0}},
      {sf::Keyboard::Scan::Up, {0, -1}},
      {sf::Keyboard::Scan::Down, {0, 1}}};

  while (window.isOpen()) {
    while (auto eventOpt = window.pollEvent()) {
      const sf::Event &event = *eventOpt;

      if (event.is<sf::Event::Closed>()) {
        window.close();
      }

      if (auto keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        auto it = directions.find(keyPressed->scancode);
        if (it != directions.end()) {
          snake.turn(it->second);
          snake.move();
        }
      }
    }
    window.clear();
    snake.render(window);
    window.display();
  }
}
