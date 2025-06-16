#include "Food.hpp"
#include "Game.hpp"
#include "Snake.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

const unsigned int WINDOW_SIZE = BOARD_WIDTH;
const float CELL_SIZE = static_cast<float>(WINDOW_SIZE) / GRID_SIZE;
const float SCORE_LABEL_HEIGHT = (CELL_SIZE - BORDER_THICKNESS) * 2;
const float SCORE_LABEL_WIDTH = WINDOW_SIZE - 2 * BORDER_THICKNESS;
const float BORDER_THICKNESS = 2.f;
const float SCORE_LABEL_PADDING = 16.f;

int main() {
  sf::Font font;
  if (!font.loadFromFile("assets/PixelOperator.ttf")) {
    std::cerr << "Error: could not load font\n";
    return EXIT_FAILURE;
  }

  sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE),
                          "SFML Snake");
  Game game(window, font);
  Score gameScore(font, 30);
  Snake snake(CELL_SIZE);
  Food food(CELL_SIZE);

  window.setFramerateLimit(60);

  sf::RectangleShape scoreBg({SCORE_LABEL_WIDTH, SCORE_LABEL_HEIGHT});
  scoreBg.setPosition({BORDER_THICKNESS, BORDER_THICKNESS});
  scoreBg.setOutlineThickness(BORDER_THICKNESS);
  scoreBg.setFillColor(sf::Color::Transparent);
  scoreBg.setOutlineColor(sf::Color::Yellow);

  std::map<sf::Keyboard::Key, sf::Vector2i> directions = {
      {sf::Keyboard::Right, {1, 0}},
      {sf::Keyboard::Left, {-1, 0}},
      {sf::Keyboard::Up, {0, -1}},
      {sf::Keyboard::Down, {0, 1}}};

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        auto key = event.key.code;
        if (key == sf::Keyboard::Enter && !game.started()) {
          game.start();
        } else if (key == sf::Keyboard::Space) {
          game.togglePause();
        } else {
          if (game.started() && !game.paused()) {
            if (auto it = directions.find(key); it != directions.end()) {
              snake.turn(it->second);
              if (!snake.move())
                game.end();
            }
          }
        }
      }
    }

    if (game.started() && snake.hasEaten(food.getPosition())) {
      snake.grow();
      food.setPosition(getRandomPosition(GRID_SIZE, GRID_SIZE));
      gameScore.increase();
    }
    if (game.over()) {
      snake.reset();
      food.setPosition(getRandomPosition(GRID_SIZE, GRID_SIZE));
      gameScore.reset();
    }

    window.clear();
    window.draw(scoreBg);
    gameScore.draw(window);

    if (game.started()) {
      snake.render(window);
      food.render(window);
    } else
      game.displayMsg();

    window.display();
  }

  return 0;
}
