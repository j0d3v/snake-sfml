#include "Snake.hpp"
#include "utils.hpp"
#include <algorithm>

Snake::Snake(float size) {
  square.setSize({size, size});
  square.setFillColor(sf::Color::Green);

  head = getRandomPosition(BOARD_SIZE, BOARD_SIZE);
  segments.push_front(head);
  direction = {0, 0};
}

void Snake::turn(sf::Vector2i dir) { direction = dir; }

bool Snake::move() {
  sf::Vector2f newHead = head;
  float step = square.getSize().x;

  newHead.x += direction.x * step;
  newHead.y += direction.y * step;

  if (newHead.x < 0 || newHead.y < 0 || newHead.x >= BOARD_SIZE ||
      newHead.y >= BOARD_SIZE)
    return false;

  if (std::find(segments.begin(), segments.end(), newHead) != segments.end())
    return false;

  head = newHead;
  segments.push_front(head);

  while (segments.size() > length)
    segments.pop_back();

  return true;
}

void Snake::render(sf::RenderWindow &window) {
  for (const auto &pos : segments) {
    square.setPosition(pos);
    window.draw(square);
  }
}

void Snake::grow() { ++length; }
