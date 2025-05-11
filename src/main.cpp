#include "Food.hpp"
#include "Snake.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
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

  const float CELL_SIZE = BOARD_WIDTH * 1.f / GRID_SIZE;
  const unsigned int SCORE_LABEL_H = CELL_SIZE * 2;
  const int BORDER_THICKNESS = 2;

  sf::RectangleShape scoreLabel;
  scoreLabel.setSize({BOARD_WIDTH - BORDER_THICKNESS * 2,
                      SCORE_LABEL_H * 1.f - BORDER_THICKNESS * 2});
  scoreLabel.setPosition({BORDER_THICKNESS, BORDER_THICKNESS});
  scoreLabel.setOutlineThickness(BORDER_THICKNESS);
  scoreLabel.setFillColor(sf::Color::Transparent);
  scoreLabel.setOutlineColor(sf::Color::Yellow);

  Snake snake(CELL_SIZE);
  Food food(CELL_SIZE);
  sf::Font font;

  if (!font.openFromFile("assets/PixelOperator.ttf")) {
    std::cerr << "Font not loaded" << std::endl;
    return 1;
  }

  unsigned int score = 0;
  unsigned int bestScore = 0;

  sf::Text currentScoreText(font, "Score : 0");
  currentScoreText.setCharacterSize(30);
  currentScoreText.setPosition({10, 3});

  sf::Text bestScoreText(font, "Score : " + std::to_string(bestScore));
  bestScoreText.setCharacterSize(30);
  bestScoreText.setPosition({BOARD_WIDTH -
                                 bestScoreText.getLocalBounds().size.x -
                                 BORDER_THICKNESS - 10,
                             3});

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
            food.setPosition(getRandomPosition(GRID_SIZE, GRID_SIZE));

            if (score > bestScore) {
              bestScore = score;
              bestScoreText.setString("Score : " + std::to_string(bestScore));
            }

            score = 0;
            currentScoreText.setString("Score : 0");
            currentGameState = GameState::Over;
          }
        } else if ((currentGameState == GameState::NotStarted ||
                    currentGameState == GameState::Over) &&
                   keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
          currentGameState = GameState::Started;
        } else if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
          if (currentGameState == GameState::Paused) {
            currentGameState = GameState::Started;
          } else {
            currentGameState = GameState::Paused;
          }
        }
      }
    }

    if (snake.hasEaten(food.getPosition())) {
      snake.grow();
      food.setPosition(getRandomPosition(GRID_SIZE, GRID_SIZE));
      currentScoreText.setString("Score : " + std::to_string(++score));
    }

    window.clear();
    window.draw(scoreLabel);
    window.draw(currentScoreText);
    window.draw(bestScoreText);

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
