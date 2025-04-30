#ifndef __SNAKE__
#define __SNAKE__

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>

class Snake {
private:
  sf::Vector2f head;
  sf::RectangleShape square;
  std::deque<sf::Vector2f> segments;
  sf::Vector2i direction;
  int length = 1;

public:
  Snake(float size);

  void turn(sf::Vector2i dir);
  bool move();
  void grow();
  void reset();
  void render(sf::RenderWindow &window);
  bool hasEaten(const sf::Vector2f &targetPos);
};

#endif
