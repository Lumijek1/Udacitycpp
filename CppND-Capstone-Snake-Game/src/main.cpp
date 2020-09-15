#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "gameStart.h"


int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  gameStarter starter;
  int highscore = starter.getCurrentHighScore();
  bool start = false;
  while(start == false){
    start = starter.start(game);
  }
  std::cout << "Game starting in 3 seconds!" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n" << std::endl;

  std::string name;
  std::cout << "Enter you name please: ";
  std::cin >> name;
  std::cout << "\n";
  if(game.GetScore() > highscore){
    std::cout << "Congratulations you set a new High Score!!!!\n" << std::endl;
  }
  starter.highScore(name, game.GetScore());
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}