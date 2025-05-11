#include "Snake.hpp"
#include "utils.hpp"
#include <SFML/System/Vector2.hpp>
#include <algorithm>

Snake::Snake(float size) {
  square.setSize({size, size});
  square.setFillColor(sf::Color::Green);

  head = getRandomPosition(GRID_SIZE, GRID_SIZE);
  segments.push_front(head);
  direction = {0, 0};
}

void Snake::turn(sf::Vector2i dir) { direction = dir; }

bool Snake::move() {
  sf::Vector2f newHead = head;
  newHead.x += direction.x;
  newHead.y += direction.y;

  if (newHead.x < 0 || newHead.y < 2 || newHead.x >= GRID_SIZE ||
      newHead.y >= GRID_SIZE)
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
  const float step = square.getSize().x;
  for (const sf::Vector2f &pos : segments) {
    square.setPosition({pos.x * step, pos.y * step});
    window.draw(square);
  }
}

void Snake::grow() { ++length; }

bool Snake::hasEaten(const sf::Vector2f &targetPos) {
  return head.x == targetPos.x && head.y == targetPos.y;
}
void Snake::reset() {
  head = getRandomPosition(GRID_SIZE, GRID_SIZE);
  length = 1;
  direction = {0, 0};
  segments.clear();
  segments.push_front(head);
}
