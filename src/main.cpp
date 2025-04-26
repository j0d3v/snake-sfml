#include "Snake.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <map>
#include <optional>

int main() {
  sf::RenderWindow window(sf::VideoMode({400, 400}), "SFML");
  window.setFramerateLimit(60);

  Snake snake(20);
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
