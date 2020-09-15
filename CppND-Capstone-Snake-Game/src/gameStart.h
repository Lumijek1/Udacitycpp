#ifndef GAMESTART_H
#define GAMESTART_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "game.h"


class gameStarter{
  public:
  	bool start(Game &game);
  	void highScore(std::string name, int score);
  	void printLeaderBoards();
  	void setDifficulty(int difficulty, Game& game);
    int getCurrentHighScore();
  	void quit();
  	
  private:
  	static bool sortByValue(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b);
    int highscore;
};


#endif