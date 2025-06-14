#include "Game.hpp"

Game::Game() : state(GameState::NotStarted) {}

// Game control methods
void Game::start() {
  if (state == GameState::NotStarted || state == GameState::Over) {
    state = GameState::Started;
  }
}
void Game::togglePause() {
  if (state == GameState::Started) {
    state = GameState::Paused;
  } else if (state == GameState::Paused) {
    state = GameState::Started;
  }
}

void Game::end() {
  if (state == GameState::Started || state == GameState::Paused) {
    state = GameState::Over;
  }
}

// State checking methods
bool Game::started() const {
  return state == GameState::Started && state != GameState::NotStarted;
}

bool Game::paused() const { return state == GameState::Paused; }

bool Game::over() const { return state == GameState::Over; }

GameState Game::getState() { return this->state; }
