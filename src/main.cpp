#include "Food.hpp"
#include "Game.hpp"
#include "Snake.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

constexpr unsigned int WINDOW_SIZE = BOARD_WIDTH;
constexpr float CELL_SIZE = static_cast<float>(WINDOW_SIZE) / GRID_SIZE;
constexpr unsigned int SCORE_LABEL_HEIGHT = CELL_SIZE * 2;
constexpr float BORDER_THICKNESS = 2.f;

sf::Text createCenteredText(sf::RenderWindow &window, const sf::Font &font,
                            const std::string &message,
                            unsigned int charSize = 24) {
  sf::Text text(message, font, charSize);
  auto bounds = text.getLocalBounds();
  text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
  text.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
  return text;
}

int main() {
  Game game;
  sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE),
                          "SFML Snake");
  window.setFramerateLimit(60);

  sf::RectangleShape scoreBg;
  scoreBg.setSize({WINDOW_SIZE - 2 * BORDER_THICKNESS,
                   SCORE_LABEL_HEIGHT - 2 * BORDER_THICKNESS});
  scoreBg.setPosition({BORDER_THICKNESS, BORDER_THICKNESS});
  scoreBg.setOutlineThickness(BORDER_THICKNESS);
  scoreBg.setFillColor(sf::Color::Transparent);
  scoreBg.setOutlineColor(sf::Color::Yellow);

  Snake snake(CELL_SIZE);
  Food food(CELL_SIZE);

  sf::Font font;
  if (!font.loadFromFile("assets/PixelOperator.ttf")) {
    std::cerr << "Error: could not load font\n";
    return EXIT_FAILURE;
  }

  unsigned int score = 0, bestScore = 0;
  sf::Text currentScore("Score: 0", font, 30);
  currentScore.setPosition(10.f, 3.f);

  sf::Text bestScoreText("Best: 0", font, 30);
  bestScoreText.setPosition(WINDOW_SIZE - bestScoreText.getLocalBounds().width -
                                BORDER_THICKNESS - 10.f,
                            3.f);

  auto startText = createCenteredText(window, font, "Press Enter to start");
  auto pauseText = createCenteredText(window, font, "Paused - Press Space");
  auto gameOverText =
      createCenteredText(window, font, "Game Over - Press Enter");

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
              if (!snake.move()) {
                game.end();
                snake.reset();
                food.setPosition(getRandomPosition(GRID_SIZE, GRID_SIZE));
                if (score > bestScore) {
                  bestScore = score;
                  bestScoreText.setString("Best: " + std::to_string(bestScore));
                }
                score = 0;
                currentScore.setString("Score: 0");
              }
            }
          }
        }
      }
    }

    if (game.started() && snake.hasEaten(food.getPosition())) {
      snake.grow();
      food.setPosition(getRandomPosition(GRID_SIZE, GRID_SIZE));
      currentScore.setString("Score: " + std::to_string(++score));
    }

    window.clear();
    window.draw(scoreBg);
    window.draw(currentScore);
    window.draw(bestScoreText);

    switch (game.getState()) {
    case GameState::NotStarted:
      window.draw(startText);
      break;
    case GameState::Started:
      snake.render(window);
      food.render(window);
      break;
    case GameState::Paused:
      window.draw(pauseText);
      break;
    case GameState::Over:
      window.draw(gameOverText);
      break;
    }

    window.display();
  }

  return 0;
}
