#include "Game.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

Game::Game(sf::RenderWindow &w, const sf::Font &font)
    : state(GameState::NotStarted), message("Press Enter to start", font, 30) {
  window = &w;
  auto bounds = message.getLocalBounds();
  message.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
  message.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);
}

// Game control methods
void Game::start() {
  if (state == GameState::NotStarted || state == GameState::Over) {
    state = GameState::Started;
  }
}
void Game::togglePause() {
  if (state == GameState::Started) {
    state = GameState::Paused;
    message.setString("Paused - Press Space");
  } else if (state == GameState::Paused) {
    state = GameState::Started;
  }
}

void Game::end() {
  if (state == GameState::Started || state == GameState::Paused) {
    state = GameState::Over;
    message.setString("Lost ! - Press Enter");
  }
}

// State checking methods
bool Game::started() const {
  return state == GameState::Started && state != GameState::NotStarted;
}

bool Game::paused() const { return state == GameState::Paused; }

bool Game::over() const { return state == GameState::Over; }

void Game::displayMsg() { window->draw(this->message); }

// Score class
Score::Score(sf::Font &font, unsigned int fontSize) : current(0), best(0) {
  currentText.setFont(font);
  currentText.setCharacterSize(fontSize);
  currentText.setFillColor(sf::Color::White);
  currentText.setString("Score: 0");

  sf::FloatRect cBounds = currentText.getLocalBounds();
  // Vertical centering
  float currentTextY = (SCORE_LABEL_HEIGHT - cBounds.height) / 2 - cBounds.top;

  currentText.setPosition(SCORE_LABEL_PADDING, currentTextY);

  bestText.setFont(font);
  bestText.setCharacterSize(fontSize);
  bestText.setFillColor(sf::Color::Yellow);
  bestText.setString("Best: 0");

  sf::FloatRect bBounds = bestText.getLocalBounds();

  // Position the scores with space-between layout and padding
  float bestTextY = (SCORE_LABEL_HEIGHT - bBounds.height) / 2 - bBounds.top;
  float bestTextX =
      SCORE_LABEL_WIDTH - (bBounds.width + bBounds.left + SCORE_LABEL_PADDING);

  bestText.setPosition(bestTextX, bestTextY);
}

// Increase current score by 1
void Score::increase() {
  current++;
  if (current > best) {
    best = current;
  }

  currentText.setString("Score: " + std::to_string(current));
  bestText.setString("Best: " + std::to_string(best));
}

void Score::reset() {
  current = 0;
  currentText.setString("Score: 0");
}

unsigned int Score::getCurrentScore() const { return current; }
unsigned int Score::getBestScore() const { return best; }

void Score::draw(sf::RenderWindow &window) {
  window.draw(currentText);
  window.draw(bestText);
}
