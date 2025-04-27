#ifndef __FOOD__
#define __FOOD__

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Food {
private:
  sf::RectangleShape square;
  sf::Vector2f position;

public:
  explicit Food(float size);

  void setPosition(const sf::Vector2f &pos);
  const sf::Vector2f &getPosition() const;

  void render(sf::RenderWindow &window);
};

#endif
