#ifndef GAME_H
#define GAME_H

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

#endif // GAME_H
