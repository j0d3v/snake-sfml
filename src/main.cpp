#include "Food.hpp"
#include "Snake.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <map>

sf::Text createCenteredText(sf::RenderWindow &window, const sf::Font &font,
                            const std::string &message,
                            unsigned int charSize = 24) {
  sf::Text text(font, message);
  text.setCharacterSize(charSize);
  auto center = text.getGlobalBounds().size / 2.f;
  auto localBounds = center + text.getLocalBounds().position;
  text.setOrigin(round(localBounds));
  text.setPosition(sf::Vector2f{window.getSize() / 2u});
  return text;
}
int main() {
  sf::RenderWindow window(sf::VideoMode({BOARD_WIDTH, BOARD_WIDTH}), "SFML");
  window.setFramerateLimit(60);

  const float cellSize = BOARD_WIDTH * 1.f / GRID_SIZE;

  Snake snake(cellSize);
  Food food(cellSize);
  sf::Font font;

  if (!font.openFromFile("assets/PixelOperator.ttf")) {
    std::cout << "Font not loaded" << std::endl;
    exit(1);
  }

  sf::Text startMsg = createCenteredText(window, font, "Press Enter to start");
  sf::Text pauseMsg =
      createCenteredText(window, font, "Paused! Press Space to resume");
  sf::Text gameOverMsg =
      createCenteredText(window, font, "Game Over! Press Enter to restart");

  enum class GameState { NotStarted, Started, Paused, Over };
  GameState currentGameState = GameState::NotStarted;

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
          if (!snake.move()) {
            snake.reset();
            currentGameState = GameState::Over;
          }
        } else if ((currentGameState == GameState::NotStarted ||
                    currentGameState == GameState::Over) &&
                   keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
          currentGameState = GameState::Started;
        } else if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
          if (currentGameState == GameState::Paused)
            currentGameState = GameState::Started;
          else
            currentGameState = GameState::Paused;
        }
      }
    }

    if (snake.hasEaten(food.getPosition())) {
      snake.grow();
      food.setPosition(getRandomPosition(GRID_SIZE, GRID_SIZE));
    }

    window.clear();
    switch (currentGameState) {
    case GameState::NotStarted:
      window.draw(startMsg);
      break;

    case GameState::Started:
      snake.render(window);
      food.render(window);
      break;
    case GameState::Paused:
      window.draw(pauseMsg);
      break;
    case GameState::Over:
      window.draw(gameOverMsg);
      break;
    }
    window.display();
  }
}
