#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

extern const unsigned int WINDOW_SIZE;
extern const float BORDER_THICKNESS;
extern const float SCORE_LABEL_HEIGHT;
extern const float SCORE_LABEL_WIDTH;
extern const float SCORE_LABEL_PADDING;

enum class GameState { NotStarted, Started, Paused, Over };

class Game {
private:
  GameState state;

public:
  Game();

  // Game control methods
  void start();
  void togglePause();
  void end();

  // State checking methods
  bool started() const;
  bool paused() const;
  bool over() const;
  GameState getState();
};

class Score {
private:
  unsigned int current;
  unsigned int best;

  sf::Text currentText;
  sf::Text bestText;

public:
  Score(sf::Font &font, unsigned int fontSize);

  void increase();
  void reset();
  unsigned int getCurrentScore() const;
  unsigned int getBestScore() const;

  void draw(sf::RenderWindow &window);
};

#endif // GAME_H
