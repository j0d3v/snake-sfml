#include "Food.hpp"
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
  Food food(cellSize);

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
    if (snake.hasEaten(food.getPosition())) {
      snake.grow();
      food.setPosition(getRandomPosition(GRID_SIZE, GRID_SIZE));
    }
    window.clear();
    snake.render(window);
    food.render(window);
    window.display();
  }
}
