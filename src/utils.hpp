#ifndef __UTILS__
#define __UTILS__

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>

const int BOARD_WIDTH = 500;
const int GRID_SIZE = 20;

inline sf::Vector2f getRandomPosition(int width, int height) {
  float x = static_cast<float>(std::rand() % width);
  float y = static_cast<float>(std::rand() % height) + 2;
  return sf::Vector2f(x, y);
}
inline sf::Vector2f round(const sf::Vector2f vector) {
  return sf::Vector2f{std::round(vector.x), std::round(vector.y)};
}

#endif
