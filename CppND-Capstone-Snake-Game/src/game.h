#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void setSpeedIncrease(double speed);
  bool setObstacles(bool obs, int numberOfObstacles);
  bool setBorder(bool ans);
  bool containsObstacle(int x, int y);
  void addObstacles();
  
 private:
  Snake snake;
  SDL_Point food;
  std::vector<SDL_Point> obstaclePoints;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  double speedIncrease{0.02};
  bool obstacles = false;
  int numberOfObstacles = 0;
  bool border = false;

  void PlaceFood();
  void Update(bool &running);
};

#endif