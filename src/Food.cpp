#include "Food.hpp"
#include "utils.hpp"

Food::Food(float size) {
  square.setSize({size, size});
  square.setFillColor(sf::Color::Red);
  position = getRandomPosition(GRID_SIZE, GRID_SIZE);
}

void Food::setPosition(const sf::Vector2f &pos) { position = pos; }

const sf::Vector2f &Food::getPosition() const { return position; }

void Food::render(sf::RenderWindow &window) {
  const float step = square.getSize().x;
  square.setPosition({position.x * step, position.y * step});
  window.draw(square);
}
