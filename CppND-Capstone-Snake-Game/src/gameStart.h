#ifndef GAMESTART_H
#define GAMESTART_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

class gameStarter{
  public:
    gameStarter();
  	void highScore(std::string name, int score);
  	void printLeaderBoards();
  	void setDifficulty(std::string difficulty);
  	void quit();
  	bool playAgain();
  	
  private:
  	static bool sortByValue(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b);
    std::string lower(std::string data);
};


#endif